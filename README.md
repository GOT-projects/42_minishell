# 42_minishell

## But du projet

Coder un bash (en plus simple).

## Détails

### Partie obligatoire

- Avoir un invite de commande avec un historique
- Gestion de l'environnement
- builtin:
  - echo (sans option sauf -n)
  - cd (chemin absolue et relatif)
  - pwd (sans option)
  - export (sans option)
  - unset (sans option)
  - env (sans option et argument)
  - exit
- Gestion des signaux
- Gestion des pipes
- Gestion des redirection d'entrée et de sortie (<, <<, >, >>)
- Traduction du wildcard *

### Bonus

- Gestion des booléens && (and) et || (or)
- Gestion des guillemets (quote)

## Compilation

```bash
make        # compile mandatory part
make bonus  # compile with && and || and *
make fclean # remove all files compilation
```

- Éxecution

```bash
./minishell # voila
```

## Crédits

En collaboration avec [waxdred](https://github.com/waxdred).

Quelques petits tests (test pas les signaux) : [tester](https://github.com/waxdred/tester_minishell42)
