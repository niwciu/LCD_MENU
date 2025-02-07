import { useState } from "react";
import { Clipboard } from "lucide-react";
import { Prism as SyntaxHighlighter } from "react-syntax-highlighter";
import vscDarkPlus from "react-syntax-highlighter/dist/cjs/styles/prism/vsc-dark-plus";

const DisplayCodeWindow = ({ code }) => {
  const [copied, setCopied] = useState(false);

  const handleCopyCode = () => {
    navigator.clipboard.writeText(code).then(() => {
      setCopied(true);
      setTimeout(() => setCopied(false), 2000);
    });
  };

  return (
    <div
      style={{
        marginTop: "20px",
        backgroundColor: "#282C34",
        padding: "16px",
        borderRadius: "8px",
        position: "relative",
        boxShadow: "0 4px 6px rgba(0, 0, 0, 0.1)",
        overflow: "hidden",
      }}
    >
      <div
        style={{
          display: "flex",
          justifyContent: "space-between",
          alignItems: "center",
          marginBottom: "8px",
        }}
      >
        <h3 style={{ color: "#fff", margin: 0, fontSize: "16px" }}>menu.c</h3>
        <button
          onClick={handleCopyCode}
          style={{
            background: "none",
            border: "none",
            cursor: "pointer",
          }}
          title={copied ? "Skopiowano!" : "Kopiuj kod"}
        >
          <Clipboard color={copied ? "#4CAF50" : "#bbb"} size={20} />
        </button>
      </div>

      <SyntaxHighlighter
        language="c"
        style={vscDarkPlus}
        showLineNumbers
        customStyle={{
          borderRadius: "4px",
          padding: "12px",
          fontSize: "14px",
        }}
      >
        {code}
      </SyntaxHighlighter>
    </div>
  );
};

export default DisplayCodeWindow;
