# ncurses-for-games
Collection of working with ncurses for text-based games and such.

# Setup

Right now I'm only concerned about targeting OSX. Make sure ncursesw is installed.

```bash
brew install ncurses
brew link ncurses # you may have to use `--force`
```

Each directory is a self-contained example. Use the Makefile in each directory to build a binary executable.

```bash
make
```

# Contents

- [Bouncy ball](/bouncyball)
- [User input](/user_input)

