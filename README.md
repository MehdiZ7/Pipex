# 🧪 Pipex (42 Project)

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white" />
  <img src="https://img.shields.io/badge/Build-Makefile-1f425f?style=for-the-badge&logo=gnu&logoColor=white" />
  <img src="https://img.shields.io/badge/School-42-black?style=for-the-badge&logo=42&logoColor=white" />
</p>

<p align="center">
  <img src="https://img.shields.io/github/repo-size/MehdiZ7/Pipex?style=flat-square" />
  <img src="https://img.shields.io/github/last-commit/MehdiZ7/Pipex?style=flat-square" />
  <img src="https://img.shields.io/github/languages/top/MehdiZ7/Pipex?style=flat-square" />
</p>

<p align="center">
  <b>Executable:</b> <code>pipex</code> • <b>Mandatory + Bonus</b> • <b>Unix pipes & processes</b>
</p>

> **Pipex** is a 42 project that reproduces shell pipelines using `fork()`, `pipe()`, `dup2()`, and `execve()`.  
> It focuses on process management, file descriptors, PATH resolution, and solid error handling.

---

## 📌 Table of Contents
- [About](#-about)
- [Features](#-features)
- [Build](#-build)
- [Usage](#-usage)
- [Examples](#-examples)
- [Bonus](#-bonus)
- [How It Works](#-how-it-works)
- [Testing](#-testing)
- [Tech Stack](#-tech-stack)
- [Author](#-author)

---

## 🔎 About

In a Unix shell, you can chain commands with pipes:

```bash
< infile cmd1 | cmd2 > outfile
```

This project asks you to implement the same behavior in C by handling:
- 🔧 **pipes** (`|`)
- 🧬 **process creation** (`fork`)
- 🔁 **I/O redirection** (`dup2`, `open`)
- 🚀 **execution** (`execve`)
- 🧭 **PATH lookup** (resolving commands like `ls`, `grep`, etc.)

---

## ✨ Features

### Mandatory
- ✅ Pipeline between **two commands**
- ✅ `infile` → `cmd1` → pipe → `cmd2` → `outfile`
- ✅ PATH resolution & command execution via `execve()`
- ✅ Proper error handling (files, permissions, command not found)
- ✅ Clean file descriptor management + waits for children

### ⭐ Bonus
- ⭐ Multiple commands: `cmd1 | cmd2 | cmd3 | ... | cmdN`
- ⭐ `here_doc` support (heredoc / limiter input)
- ⭐ Dedicated Makefile rules for bonus build & cleanup

---

## 🛠️ Build

Clone and compile:

```bash
git clone https://github.com/MehdiZ7/Pipex.git
cd Pipex
make
```

### Makefile Rules
**Mandatory:**
```bash
make
make clean
make fclean
make re
```

**Bonus:**
```bash
make bonus
make clean_bonus
make fclean_bonus
```

---

## 🚀 Usage

### Mandatory (2 commands)

```bash
./pipex infile "cmd1 args" "cmd2 args" outfile
```

Equivalent to:

```bash
< infile cmd1 args | cmd2 args > outfile
```

**Arguments:**
- `infile` : input file
- `"cmd1 args"` : first command (string, can include arguments)
- `"cmd2 args"` : second command (string, can include arguments)
- `outfile` : output file (created/truncated)

---

## 🧩 Examples

### Example 1 — basic pipeline
```bash
./pipex infile "cat" "wc -l" outfile
```

Equivalent to:
```bash
< infile cat | wc -l > outfile
```

### Example 2 — grep + sort
```bash
./pipex infile "grep hello" "sort -r" outfile
```

Equivalent to:
```bash
< infile grep hello | sort -r > outfile
```

---

## ⭐ Bonus

### 🔁 Multiple Pipes (N commands)

```bash
./pipex infile "cmd1" "cmd2" "cmd3" ... "cmdN" outfile
```

Equivalent to:

```bash
< infile cmd1 | cmd2 | cmd3 | ... | cmdN > outfile
```

✅ One process per command, connected through pipes.

---

### 📝 here_doc (Heredoc)

`here_doc` allows you to type input directly in the terminal until a limiter is reached.

```bash
./pipex here_doc LIMITER "cmd1" "cmd2" outfile
```

Equivalent to:

```bash
cmd1 << LIMITER | cmd2 >> outfile
```

Notes:
- `outfile` is opened in **append mode** (`>>`) in `here_doc` mode.
- The program reads from `stdin` until `LIMITER` is encountered.

---

## 🧠 How It Works

### Mandatory pipeline (2 commands)

1. Create a pipe → `(read_end, write_end)`
2. Fork child #1:
   - `stdin`  ← `infile`
   - `stdout` → pipe write end
   - `execve(cmd1)`
3. Fork child #2:
   - `stdin`  ← pipe read end
   - `stdout` → `outfile`
   - `execve(cmd2)`
4. Parent:
   - closes unused fds
   - waits for children (`waitpid`)

### Bonus (N commands)
Same idea, but repeated:
- each command gets its own process
- pipes connect each step of the chain
- careful fd closing prevents leaks & deadlocks

---

## 🧪 Testing

Compare with the real shell output:

```bash
# Your program
./pipex infile "cmd1" "cmd2" outfile

# Shell reference
< infile cmd1 | cmd2 > outfile_ref

diff -u outfile_ref outfile
```

### Leak / FD checks
```bash
valgrind --leak-check=full --track-fds=yes ./pipex infile "cat" "wc -l" outfile
```

---

## 🧰 Tech Stack

- **C**
- **Makefile**
- Unix syscalls:
  - `fork()`, `pipe()`, `dup2()`, `execve()`
  - `waitpid()`, `open()`, `close()`, `access()`

---

## 👤 Author

**MehdiZ7**

- GitHub: [@MehdiZ7](https://github.com/MehdiZ7)
