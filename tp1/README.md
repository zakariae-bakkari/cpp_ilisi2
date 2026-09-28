# TP 1 — Pile générique et bibliothèque dynamique libpile.so

Module Programmation Orientée Objet Avancée et Design Patterns (C++, Linux). Dépôt : [cpp_ilisi2](../).

Pile générique (`Pile<T>`, `PileTableau<T>`, `PileListe<T>`) et analyseur d'expressions
mathématiques (vérification, évaluation, conversions infixe ↔ préfixe), compilés en
bibliothèque dynamique `libpile.so` (équivalent Linux d'une DLL).

## Compilation (Linux)

```bash
make          # construit libpile.so puis les programmes de test
make run      # exécute test_pile, test_expression, test_conversion
make clean    # supprime les fichiers générés
```

## Organisation

| Dossier / fichier | Contenu |
|---|---|
| `include/` | en-têtes (`.h`) et implémentations des templates (`.tpp`) |
| `src/PileTableau.cpp`, `PileListe.cpp`, `Expression.cpp` | sources de `libpile.so` |
| `src/test_*.cpp` | programmes de test des trois exercices |
| `guide/` | guide PDF : bibliothèques `.so` / `.a` et fichiers `.tpp` |
| `rapport/` | rapport du TP (LaTeX) |

## Utiliser la bibliothèque dans un autre programme

```bash
g++ -Iinclude main.cpp -L. -lpile -Wl,-rpath,'$ORIGIN' -o main
```

`libpile.so` fonctionne uniquement sous Linux ; pour Windows, il faut recompiler les
sources en `.dll` (voir `guide/guide_bibliotheques.pdf`, section 6).
