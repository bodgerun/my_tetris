# Tetris

My own implementation of the classic tetris game.

---

Controls:

| Key | Meaning |
|---|---|
| `<Space>`/`<Enter>` | start / pause / resume |
| `<D>` | show / hide debug info |
| `<Left>` | move the piece to the left |
| `<Right>` | move the piece to the right |
| `<Down>` | drop the piece |
| `<Up>` | rotate the piece |
| `<Esc>` | exit |

---

The records are stored across sessions.

---

Internally, the game is based on the *Final State Machine* (*FSM*) model.
To see details:
```Shell
$ cd src
$ make diagram
```

---

Unit tests (`check`-based) are included.
