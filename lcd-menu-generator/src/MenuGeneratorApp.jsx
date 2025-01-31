import { useState } from 'react';
import { FaSave, FaFolderOpen, FaPlus, FaTrash, FaArrowUp, FaArrowDown, FaEdit } from 'react-icons/fa'; // Dodajemy ikony

// Komponent pojedynczego obiektu w menu (może mieć podobiekty)
const MenuItem = ({ item, onRename, onMoveUp, onMoveDown, onDelete, onAddChild, parentId }) => {
  return (
    <div style={{ display: 'flex', alignItems: 'center', marginBottom: '10px', paddingLeft: `${item.level * 20}px` }}>
      {/* Pole edycji nazwy obiektu */}
      <input
        type="text"
        value={item.displayName}
        onChange={(e) => onRename(item.id, e.target.value)}
        style={{
          fontSize: '16px',
          padding: '5px',
          flexGrow: 1,
          marginRight: '10px',
          borderRadius: '4px',
        }}
      />
      
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

  // Funkcja do dodawania nowego obiektu (głównego)
  const addMenuItem = () => {
    setMenuItems([
      ...menuItems,
      { id: `menu_${idCounter}`, displayName: `menu_${idCounter}`, level: 0, children: [] }
    ]);
    setIdCounter(idCounter + 1); // Zwiększ ID
  };

  // Funkcja do zmiany nazwy obiektu (tylko zmienia widoczną nazwę)
  const renameMenuItem = (id, newName) => {
    const updatedItems = updateItemName(menuItems, id, newName);
    setMenuItems(updatedItems);
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
  };

  // Funkcja do usuwania obiektu (najwyższy poziom lub podmenu)
  const deleteMenuItem = (id, parentId) => {
    const newMenuItems = deleteItem(menuItems, id, parentId);
    setMenuItems(newMenuItems);
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
      };
      reader.readAsText(file);
    }
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
        />
        {item.children.length > 0 && (
          <div style={{ marginLeft: '20px' }}>
            {renderMenuItems(item.children, item.id)}
          </div>
        )}
      </div>
    ));
  };

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
    </div>
  );
};

export default MenuGeneratorApp;