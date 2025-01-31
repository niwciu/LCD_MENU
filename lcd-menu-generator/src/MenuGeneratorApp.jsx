import { useState } from 'react';
import { FaSave, FaFolderOpen, FaPlus, FaTrash, FaArrowUp, FaArrowDown, FaEdit } from 'react-icons/fa'; // Dodajemy ikony

// Komponent pojedynczego obiektu w menu (może mieć podobiekty)
const MenuItem = ({ item, onRename, onMoveUp, onMoveDown, onDelete, onAddChild, showCallbackName, parentId }) => {
  const isEditable = item.children.length === 0; // Jeśli obiekt nie ma dzieci, pole jest edytowalne
  console.log(showCallbackName);  // Sprawdź wartość w konsoli
  return (
    <div style={{ display: 'flex', alignItems: 'center', marginBottom: '10px', paddingLeft: `${item.level * 20}px` }}>
      {/* Pole edycji nazwy obiektu */}
      <input
        type="text"
        value={item.displayName}
        onChange={(e) => onRename(item.id, e.target.value)}
        style={{
          fontSize: '14px',
          padding: '5px',
          flexGrow: 1,
          marginRight: '10px',
          borderRadius: '4px',
          width: '150px',
        }}
      />

      {/* Pole tekstowe z podpowiedzią */}
    {showCallbackName && (
      <input
        type="text"
        placeholder={isEditable ? "place callback function name..." : "not available for parent objects"}
        disabled={!isEditable} // Jeśli obiekt ma dzieci, pole jest wyłączone
        style={{
          fontSize: '13px',
          padding: '5px',
          marginRight: '10px',
          width: '250px',
          textAlign: 'left',
          border: '1px solid #ddd',
          borderRadius: '4px',
          backgroundColor: isEditable ? '' : '#000000', // Zmieniamy tło na szare, gdy pole jest wyłączone
        }}
      />
      )
    }
      
      {/* Wyświetlanie ID obiektu w nieedytowalnym polu */}
      <input
        type="text"
        value={"ID: " + item.id}
        readOnly
        style={{
          fontSize: '14px',
          padding: '5px',
          marginRight: '10px',
          width: '150px',
          textAlign: 'left',
          backgroundColor: '#333',
          color: '#fff',
          border: '1px solid #ddd',
          borderRadius: '4px',
        }}
      />

      {/* Przycisk przesunięcia w górę */}
      <button
        onClick={() => onMoveUp(item.id, parentId)}
        style={{
          padding: '5px 10px',
          fontSize: '16px',
          marginRight: '5px',
          cursor: 'pointer',
          borderRadius: '4px',
        }}
      >
        <FaArrowUp />
      </button>
      
      {/* Przycisk przesunięcia w dół */}
      <button
        onClick={() => onMoveDown(item.id, parentId)}
        style={{
          padding: '5px 10px',
          fontSize: '16px',
          cursor: 'pointer',
          borderRadius: '4px',
        }}
      >
        <FaArrowDown />
      </button>
      
      {/* Przycisk kosza - usuwanie obiektu */}
      <button
        onClick={() => onDelete(item.id, parentId)}
        style={{
          padding: '5px 10px',
          fontSize: '16px',
          marginLeft: '5px',
          cursor: 'pointer',
          borderRadius: '4px',
        }}
      >
        <FaTrash />
      </button>
      
      {/* Przycisk + (dodawanie podobiektu) */}
      <button
        onClick={() => onAddChild(item.id, parentId)}
        style={{
          padding: '5px 10px',
          fontSize: '16px',
          marginLeft: '5px',
          cursor: 'pointer',
          borderRadius: '4px',
        }}
      >
        <FaPlus />
      </button>
    </div>
  );
};

// Komponent główny aplikacji
const MenuGeneratorApp = () => {
  const [menuItems, setMenuItems] = useState([]);
  const [idCounter, setIdCounter] = useState(1);  // Licznik dla unikalnych ID
  const [menuDepth, setMenuDepth] = useState(0); // Głębokość menu
  const [showCallbackName, setShowCallbackName] = useState(false); // Stan dla globalnego checkboxa
  // Funkcja do zmiany stanu checkboxa
  const toggleCallbackNameVisibility = () => {
    setShowCallbackName(prevState => !prevState);
  };

  // Funkcja do obliczania głębokości menu
  const calculateDepth = (items) => {
    let depth = 0;

    const calculate = (items, level) => {
      items.forEach(item => {
        depth = Math.max(depth, level + 1); // Dodajemy +1, ponieważ poziom 0 jest już dla samego obiektu głównego
        if (item.children.length > 0) {
          calculate(item.children, level + 1);
        }
      });
    };

    calculate(items, 0);
    return depth;
  };


  // Funkcja do dodawania nowego obiektu (głównego)
  const addMenuItem = () => {
    const newItem = { id: `menu_${idCounter}`, displayName: `menu_${idCounter}`, level: 0, children: [] };
    setMenuItems([...menuItems, newItem]);
    setIdCounter(idCounter + 1); // Zwiększ ID
    setMenuDepth(calculateDepth([...menuItems, newItem])); // Aktualizujemy głębokość
  };

  // Funkcja do zmiany nazwy obiektu (tylko zmienia widoczną nazwę)
  const renameMenuItem = (id, newName) => {
    const updatedItems = updateItemName(menuItems, id, newName);
    setMenuItems(updatedItems);
    setMenuDepth(calculateDepth(updatedItems)); // Aktualizujemy głębokość
  };

  // Funkcja pomocnicza do zmiany nazwy obiektu
  const updateItemName = (items, id, newName) => {
    return items.map(item => {
      if (item.id === id) {
        return { ...item, displayName: newName };
      }
      if (item.children.length > 0) {
        item.children = updateItemName(item.children, id, newName);
      }
      return item;
    });
  };

  // Funkcja pomocnicza do przesuwania obiektu na najwyższym poziomie
  const moveItemAtTopLevel = (items, id, direction) => {
    const index = items.findIndex(item => item.id === id);
    if (index === -1) return items; // Jeśli element nie istnieje, zwróć oryginalną listę

    const newItems = [...items];
    if (direction === 'up' && index > 0) {
      const [movedItem] = newItems.splice(index, 1); // Usuwamy element
      newItems.splice(index - 1, 0, movedItem); // Wstawiamy go w nowe miejsce
    } else if (direction === 'down' && index < newItems.length - 1) {
      const [movedItem] = newItems.splice(index, 1); // Usuwamy element
      newItems.splice(index + 1, 0, movedItem); // Wstawiamy go w nowe miejsce
    }
    return newItems; // Zwracamy nową tablicę
  };

  // Funkcja pomocnicza do przesuwania obiektu w obrębie jego rodzica
  const moveItemWithParent = (items, id, parentId, direction) => {
    return items.map(item => {
      // Jeśli mamy element z odpowiednim parentId
      if (item.id === parentId) {
        const index = item.children.findIndex(child => child.id === id);
        if (index === -1) return item; // Jeśli element nie istnieje, zwróć oryginalny obiekt

        const newChildren = [...item.children];
        if (direction === 'up' && index > 0) {
          const [movedItem] = newChildren.splice(index, 1); // Usuwamy element
          newChildren.splice(index - 1, 0, movedItem); // Wstawiamy go w nowe miejsce
        } else if (direction === 'down' && index < newChildren.length - 1) {
          const [movedItem] = newChildren.splice(index, 1); // Usuwamy element
          newChildren.splice(index + 1, 0, movedItem); // Wstawiamy go w nowe miejsce
        }
        return { ...item, children: newChildren }; // Zwracamy obiekt z nowymi dziećmi
      }

      // Rekurencyjnie przesuwamy w podmenu
      if (item.children.length > 0) {
        item.children = moveItemWithParent(item.children, id, parentId, direction);
      }

      return item; // Zwracamy niezmieniony element
    });
  };

  // Funkcja do przesuwania obiektu w górę w obrębie jego rodzica (albo na najwyższym poziomie)
  const moveUp = (id, parentId) => {
    let updatedItems;
    
    if (parentId === null) {
      updatedItems = moveItemAtTopLevel(menuItems, id, 'up');  // Jeśli to najwyższy poziom, przesuwamy w menu głównym
    } else {
      updatedItems = moveItemWithParent(menuItems, id, parentId, 'up'); // Przesuwanie wewnątrz podmenu
    }

    setMenuItems(updatedItems); // Zaktualizuj stan
    setMenuDepth(calculateDepth(updatedItems)); // Aktualizujemy głębokość
  };

  // Funkcja do przesuwania obiektu w dół w obrębie jego rodzica (albo na najwyższym poziomie)
  const moveDown = (id, parentId) => {
    let updatedItems;
    
    if (parentId === null) {
      updatedItems = moveItemAtTopLevel(menuItems, id, 'down');  // Jeśli to najwyższy poziom, przesuwamy w menu głównym
    } else {
      updatedItems = moveItemWithParent(menuItems, id, parentId, 'down'); // Przesuwanie wewnątrz podmenu
    }

    setMenuItems(updatedItems); // Zaktualizuj stan
    setMenuDepth(calculateDepth(updatedItems)); // Aktualizujemy głębokość
  };

  // Funkcja do usuwania obiektu (najwyższy poziom lub podmenu)
  const deleteMenuItem = (id, parentId) => {
    const newMenuItems = deleteItem(menuItems, id, parentId);
    setMenuItems(newMenuItems);
    setMenuDepth(calculateDepth(newMenuItems)); // Aktualizujemy głębokość
  };

  // Funkcja pomocnicza do usuwania obiektu
  const deleteItem = (items, id, parentId) => {
    return items.filter(item => {
      // Jeśli parentId jest null, to znaczy, że usuwamy element z najwyższego poziomu
      if (parentId === null) {
        return item.id !== id;  // Usuwamy element z głównej listy
      }

      // Jeśli parentId jest ustawione, szukamy dziecka w obrębie tego rodzica
      if (item.id === parentId) {
        item.children = item.children.filter(child => child.id !== id);  // Usuwamy dziecko
      }

      // Rekurencyjnie usuwamy w podmenu
      if (item.children.length > 0) {
        item.children = deleteItem(item.children, id, parentId);
      }

      return true;  // Zwracamy elementy, które nie zostały usunięte
    });
  };

  // Funkcja pomocnicza do dodawania podobiektu
  const addChildMenuItem = (parentId) => {
    const parentItem = findItemById(menuItems, parentId);
    if (parentItem) {
      const childId = `${parentItem.id}_${parentItem.children.length + 1}`;
      const childItem = { id: childId, displayName: childId, level: parentItem.level + 1, children: [] };

      const updatedItems = addItem(menuItems, parentId, childItem);
      setMenuItems(updatedItems);
      setMenuDepth(calculateDepth(updatedItems)); // Aktualizujemy głębokość
    }
  };

  // Funkcja pomocnicza do dodawania podobiektu
  const addItem = (items, parentId, newItem) => {
    return items.map(item => {
      if (item.id === parentId) {
        return { ...item, children: [...item.children, newItem] };
      }
      if (item.children.length > 0) {
        item.children = addItem(item.children, parentId, newItem);
      }
      return item;
    });
  };

  // Funkcja pomocnicza do znajdowania obiektu w hierarchii
  const findItemById = (items, id) => {
    for (let item of items) {
      if (item.id === id) return item;
      if (item.children.length > 0) {
        const child = findItemById(item.children, id);
        if (child) return child;
      }
    }
    return null;
  };

  // Funkcja do zapisu struktury menu do pliku
  const saveMenuToFile = () => {
    const blob = new Blob([JSON.stringify(menuItems)], { type: 'application/json' });
    const link = document.createElement('a');
    link.href = URL.createObjectURL(blob);
    link.download = 'menu_structure.json';
    link.click();
  };

  // Funkcja do wczytania struktury menu z pliku
  const loadMenuFromFile = (event) => {
    const file = event.target.files[0];
    if (file) {
      const reader = new FileReader();
      reader.onload = () => {
        const data = JSON.parse(reader.result);
        setMenuItems(data);
  
        // Obliczanie głębokości po załadowaniu menu z pliku
        const depth = calculateDepth(data);
        setMenuDepth(depth);  // Ustawienie głębokości
  
        // Znajdź najwyższe ID w strukturze
        const maxId = getMaxIdFromItems(data);
        setIdCounter(maxId + 1);  // Ustaw idCounter na najwyższe ID + 1
      };
      reader.readAsText(file);
    }
  };

  // Funkcja pomocnicza do znajdowania najwyższego ID w strukturze
  const getMaxIdFromItems = (items) => {
    let maxId = 0;
    items.forEach(item => {
      const numericId = parseInt(item.id.split('_')[1], 10);
      maxId = Math.max(maxId, numericId);

      if (item.children && item.children.length > 0) {
        maxId = Math.max(maxId, getMaxIdFromItems(item.children)); // Rekurencja dla dzieci
      }
    });
    return maxId;
  };

  // Funkcja aktualizująca ID
  const resetIds = (items, level = 1) => {
    let newIdCounter = 1; // Licznik do nowych ID
    return items.map(item => {
      // Generujemy nowe ID zgodnie z poziomem
      const newId = `menu_${level}_${newIdCounter}`;
      
      // Tworzymy nowy obiekt z nowym ID, ale zachowujemy oryginalną nazwę
      const newItem = { ...item, id: newId, children: [] };
  
      // Zwiększamy licznik ID
      newIdCounter++;
  
      // Jeśli element ma dzieci, to rekurencyjnie aktualizujemy ich ID
      if (item.children.length > 0) {
        newItem.children = resetIds(item.children, level + 1); // Zwiększamy poziom
      }
  
      return newItem;
    });
  };

  // Funkcja resetująca ID w całym menu z zachowaniem hierarchii
  const resetMenuIds = () => {
    let counter = 1; // Licznik, który będzie nadawał ID

    // Funkcja do nadawania nowych ID rekurencyjnie
    const updateIdsRecursively = (items, parentId = '') => {
      return items.map((item, index) => {
        // Nadanie nowego ID na podstawie rodzica
        const newId = parentId ? `${parentId}_${index + 1}` : `menu_${counter++}`;
        const updatedItem = { ...item, id: newId };

        // Zaktualizowanie dzieci (jeśli istnieją)
        if (updatedItem.children && updatedItem.children.length > 0) {
          updatedItem.children = updateIdsRecursively(updatedItem.children, newId);  // Rekurencyjnie nadawaj ID dzieciom
        }

        return updatedItem;
      });
    };

  // Zaktualizowanie głównych elementów menu
    const updatedMenuItems = updateIdsRecursively(menuItems);
    setMenuItems(updatedMenuItems); // Zaktualizowanie stanu
  };
  
  // Renderowanie elementów menu
  const renderMenuItems = (items, parentId = null) => {
    return items.map(item => (
      <div key={item.id}>
        <MenuItem
          item={item}
          parentId={parentId}
          onRename={renameMenuItem}
          onMoveUp={moveUp}
          onMoveDown={moveDown}
          onDelete={deleteMenuItem}
          onAddChild={addChildMenuItem}
          showCallbackName={showCallbackName}
        />
        {item.children.length > 0 && (
          <div style={{ marginLeft: '20px' }}>
            {renderMenuItems(item.children, item.id)}
          </div>
        )}
      </div>
    ));
  };
  console.log('showCallbackName:', showCallbackName); // Tu sprawdzisz wartość stanu
  return (
    <div style={{ padding: '20px', fontFamily: 'Arial, sans-serif' }}>
      <h1 style={{ marginBottom: '10px' }}>Menu Generator</h1>
      <div style={{ display: 'flex', alignItems: 'center', justifyContent: 'center', marginBottom: '20px' }}>
        {/* Przycisk zapisu */}
        <button
          onClick={saveMenuToFile}
          style={{
            padding: '5px 10px',
            fontSize: '20px',
            marginLeft: '10px',
            cursor: 'pointer',
            borderRadius: '50%',
            border: '2px solid #4CAF50',
            backgroundColor: '#fff',
            color: '#4CAF50',
          }}
        >
          <FaSave />
        </button>

        {/* Przycisk wczytywania */}
        <input
          type="file"
          onChange={loadMenuFromFile}
          style={{ display: 'none' }}
          id="file-input"
        />
        <button
          onClick={() => document.getElementById('file-input').click()}
          style={{
            padding: '5px 10px',
            fontSize: '20px',
            marginLeft: '10px',
            cursor: 'pointer',
            borderRadius: '50%',
            border: '2px solid #4CAF50',
            backgroundColor: '#fff',
            color: '#4CAF50',
          }}
        >
          <FaFolderOpen />
        </button>

        {/* Przycisk nadawania nowych ID */}
        <button
        onClick={resetMenuIds}
        style={{
          padding: '5px 10px',
          fontSize: '20px',
          marginLeft: '10px',
          cursor: 'pointer',
          borderRadius: '50%',
          border: '2px solid #4CAF50',
          backgroundColor: '#fff',
          color: '#4CAF50',
        }}
      >
        <FaEdit />
      </button>

      </div>

      {/* Globalny checkbox */}
      <div>
        <input
          type="checkbox"
          checked={showCallbackName}
          onChange={toggleCallbackNameVisibility}
          style={{ marginRight: '10px' }}
        />
        <span>Enable menu items execute callback generation</span>
      </div>
      <div style={{ display: 'flex', alignItems: 'center', marginBottom: '20px', marginTop: '40px' }}>
        <h3 style={{ margin: 0, paddingLeft: '20px' }}>MENU</h3>

        {/* Przycisk dodawania menu */}
        <button
          onClick={addMenuItem}
          style={{
            padding: '5px 10px',
            fontSize: '16px',
            marginLeft: '5px',
            cursor: 'pointer',
            borderRadius: '4px',
          }}
        >
          <FaPlus />
        </button>
      </div>
      <div style={{ paddingLeft: '40px' }}>
        {renderMenuItems(menuItems)}
      </div>
      <div style={{ padding: '20px' }}>
        <h4 style={{ margin: '0' }}>MAX MENU DEPTH: {menuDepth}</h4>
      </div>
    </div>
  );
};

export default MenuGeneratorApp;
