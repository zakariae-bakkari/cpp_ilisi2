"""Arbre rouge-noir : insertion, réparation, vérification et affichage.

None représente une feuille nil (toujours noire).
"""
import math
import random

ROUGE, NOIR = "R", "N"


class Noeud:
    def __init__(self, cle, couleur=ROUGE, parent=None):
        self.cle = cle
        self.couleur = couleur
        self.gauche = None   # None = feuille nil (noire)
        self.droite = None
        self.parent = parent


def est_rouge(n):
    # Un nil (None) compte comme NOIR : c'est la règle 3.
    return n is not None and n.couleur == ROUGE


def nom(n):
    return "nil" if n is None else f"{n.cle}({n.couleur})"


class ArbreRN:
    def __init__(self, bavard=False):
        self.racine = None
        self.bavard = bavard
        self.stats = {"A": 0, "B": 0, "C": 0}

    def _log(self, texte=""):
        if self.bavard:
            print(texte)

    # ------------------------------------------------------------------
    # Rotations
    # ------------------------------------------------------------------
    def rotation_gauche(self, x):
        """x descend à gauche, son fils droit y monte à sa place."""
        y = x.droite
        # 1) le sous-arbre gauche de y (B) devient le fils droit de x
        x.droite = y.gauche
        if y.gauche is not None:
            y.gauche.parent = x
        # 2) y prend la place de x chez le parent de x
        y.parent = x.parent
        if x.parent is None:
            self.racine = y              # piège : penser à la racine !
        elif x is x.parent.gauche:
            x.parent.gauche = y
        else:
            x.parent.droite = y
        # 3) x devient le fils gauche de y
        y.gauche = x
        x.parent = y

    def rotation_droite(self, x):
        """Miroir exact de rotation_gauche."""
        y = x.gauche
        x.gauche = y.droite
        if y.droite is not None:
            y.droite.parent = x
        y.parent = x.parent
        if x.parent is None:
            self.racine = y
        elif x is x.parent.droite:
            x.parent.droite = y
        else:
            x.parent.gauche = y
        y.droite = x
        x.parent = y

    # ------------------------------------------------------------------
    # Insertion
    # ------------------------------------------------------------------
    def inserer(self, cle):
        # Étape a) descente comme dans un arbre binaire de recherche
        parent, courant, chemin = None, self.racine, []
        while courant is not None:
            chemin.append(str(courant.cle))
            parent = courant
            if cle < courant.cle:
                courant = courant.gauche
            elif cle > courant.cle:
                courant = courant.droite
            else:
                self._log(f"{cle} est déjà présent : on ne fait rien.")
                return False

        # Étape b) le nouveau nœud est ROUGE (la hauteur noire ne change pas)
        n = Noeud(cle, ROUGE, parent)
        if parent is None:
            self.racine = n
            place = "arbre vide : N devient la racine"
        elif cle < parent.cle:
            parent.gauche = n
            place = f"à gauche de {parent.cle}"
        else:
            parent.droite = n
            place = f"à droite de {parent.cle}"

        self._log(f"=== Insertion de {cle} ===")
        self._log(f"Chemin : {' -> '.join(chemin) if chemin else '(aucun)'} ; N placé {place}")
        self._log("Arbre AVANT réparation :")
        if self.bavard:
            self.afficher()

        # Étapes c) et d)
        self._reparer(n)

        self._log("Arbre APRÈS réparation :")
        if self.bavard:
            self.afficher()
            self._log()
        return True

    def _reparer(self, n):
        # Étape c) tant que le parent est rouge, on a un rouge-rouge (règle 4)
        if not est_rouge(n.parent) and n.parent is not None:
            self._log(f"Parent P={nom(n.parent)} noir : rien à réparer.")
        while est_rouge(n.parent):
            p = n.parent
            g = p.parent          # existe : P rouge n'est jamais la racine
            if p is g.gauche:     # ---------- P à GAUCHE de G ----------
                u = g.droite
                cote_p = "gauche"
            else:                 # ---------- cas miroir : P à DROITE ----------
                u = g.gauche
                cote_p = "droite"
            self._log(f"N={nom(n)}, P={nom(p)} rouge, G={nom(g)}, U={nom(u)}")

            if est_rouge(u):
                # Cas A : oncle rouge -> recoloration, puis on remonte en G
                self.stats["A"] += 1
                p.couleur = NOIR
                u.couleur = NOIR
                g.couleur = ROUGE
                self._log(f"  Cas A (oncle rouge) : {p.cle} et {u.cle} en noir, "
                          f"{g.cle} en rouge ; on recommence avec N={g.cle}")
                n = g             # piège : il faut REBOUCLER
                continue

            # Oncle noir ou nil : on regarde la forme
            cote_n = "gauche" if n is p.gauche else "droite"
            if cote_n != cote_p:
                # Cas C : zig-zag -> rotation en P pour obtenir une ligne
                self.stats["C"] += 1
                self._log(f"  Cas C (oncle noir, zig-zag {cote_p}-{cote_n}) : "
                          f"rotation {'gauche' if cote_p == 'gauche' else 'droite'} en {p.cle}")
                if cote_p == "gauche":
                    self.rotation_gauche(p)
                else:
                    self.rotation_droite(p)
                n, p = p, n       # l'ancien N est maintenant le parent

            # Cas B : ligne -> rotation en G + échange des couleurs de P et G
            self.stats["B"] += 1
            if cote_p == "gauche":
                self.rotation_droite(g)
            else:
                self.rotation_gauche(g)
            p.couleur, g.couleur = g.couleur, p.couleur
            self._log(f"  Cas B (oncle noir, ligne {cote_p}-{cote_p}) : "
                      f"rotation {'droite' if cote_p == 'gauche' else 'gauche'} en {g.cle}, "
                      f"{p.cle} devient noir et {g.cle} rouge")
            # P est noir maintenant : la boucle s'arrête

        # Règle 2 : la racine est toujours remise en noir
        if self.racine.couleur == ROUGE:
            self._log(f"Racine {self.racine.cle} rouge -> remise en noir (règle 2)")
            self.racine.couleur = NOIR

    # ------------------------------------------------------------------
    # Vérification des règles
    # ------------------------------------------------------------------
    def verifier(self):
        """Renvoie la liste des règles violées (liste vide = arbre correct)."""
        erreurs = []
        r = self.racine
        if r is None:
            return erreurs
        if r.couleur != NOIR:
            erreurs.append(f"Règle 2 : la racine {r.cle} est rouge")
        if r.parent is not None:
            erreurs.append("Lien parent : la racine a un parent")

        def rec(n, mini, maxi):
            """Renvoie la hauteur noire de n (un nil compte pour 1)."""
            if n is None:
                return 1
            if n.couleur not in (ROUGE, NOIR):
                erreurs.append(f"Règle 1 : {n.cle} n'est ni rouge ni noir")
            if (mini is not None and n.cle <= mini) or (maxi is not None and n.cle >= maxi):
                erreurs.append(f"Ordre ABR : {n.cle} est mal placé")
            for e in (n.gauche, n.droite):
                if e is not None and e.parent is not n:
                    erreurs.append(f"Lien parent : {e.cle} ne pointe pas vers {n.cle}")
            if n.couleur == ROUGE:
                for e in (n.gauche, n.droite):
                    if est_rouge(e):
                        erreurs.append(f"Règle 4 : rouge-rouge entre {n.cle} et {e.cle}")
            hg = rec(n.gauche, mini, n.cle)
            hd = rec(n.droite, n.cle, maxi)
            if hg != hd:
                erreurs.append(f"Règle 5 : sous {n.cle}, hauteur noire {hg} à gauche "
                               f"et {hd} à droite")
            return max(hg, hd) + (1 if n.couleur == NOIR else 0)

        rec(r, None, None)
        return erreurs

    # ------------------------------------------------------------------
    # Outils
    # ------------------------------------------------------------------
    def hauteur(self, n="debut"):
        if n == "debut":
            n = self.racine
        if n is None:
            return 0
        return 1 + max(self.hauteur(n.gauche), self.hauteur(n.droite))

    def parcours_infixe(self):
        res = []

        def rec(n):
            if n is not None:
                rec(n.gauche)
                res.append(n.cle)
                rec(n.droite)
        rec(self.racine)
        return res

    def chemins_vers_nil(self):
        """Liste (chemin, nombre de noirs sans compter le nil)."""
        res = []

        def rec(n, chemin, noirs):
            if n is None:
                res.append((chemin + ["nil"], noirs))
                return
            noirs += 1 if n.couleur == NOIR else 0
            rec(n.gauche, chemin + [nom(n)], noirs)
            rec(n.droite, chemin + [nom(n)], noirs)
        rec(self.racine, [], 0)
        return res

    def afficher(self, nils=False):
        """Affiche l'arbre couché : g = fils gauche, d = fils droit."""
        if self.racine is None:
            print("(arbre vide)")
            return
        print(nom(self.racine))

        def rec(n, prefixe):
            enfants = [("g", n.gauche), ("d", n.droite)]
            if not nils and n.gauche is None and n.droite is None:
                return
            for i, (cote, e) in enumerate(enfants):
                dernier = i == 1
                print(prefixe + ("└── " if dernier else "├── ") + f"{cote}: {nom(e)}")
                if e is not None:
                    rec(e, prefixe + ("    " if dernier else "│   "))
        rec(self.racine, "")


# ======================================================================
# Tests
# ======================================================================
def construire(cles):
    a = ArbreRN()
    for c in cles:
        a.inserer(c)
    return a


def test_exemple():
    print("#" * 60)
    print("# TEST 1 : exemple 41, 38, 31, 12, 19, 8, 50, 55")
    print("#" * 60)
    a = ArbreRN(bavard=True)
    for c in [41, 38, 31, 12, 19, 8, 50, 55]:
        a.inserer(c)
    print("Arbre final avec les feuilles nil :")
    a.afficher(nils=True)
    print("\nChemins racine -> nil (noirs comptés sans le nil) :")
    for chemin, noirs in a.chemins_vers_nil():
        print(f"  {' -> '.join(chemin):40s} noirs = {noirs}")
    print("verifier() :", a.verifier() or "aucune règle violée")
    print("Cas utilisés :", a.stats, "| hauteur :", a.hauteur())
    print()


def test_aleatoire():
    print("#" * 60)
    print("# TEST 2 : suites aléatoires (verifier() après chaque insertion)")
    print("#" * 60)
    random.seed(2026)
    nb_suites, nb_insertions = 300, 0
    for _ in range(nb_suites):
        cles = random.sample(range(10_000), random.randint(1, 300))
        a = ArbreRN()
        for c in cles:
            a.inserer(c)
            nb_insertions += 1
            erreurs = a.verifier()
            assert not erreurs, erreurs
        assert a.parcours_infixe() == sorted(cles)
        n = len(cles)
        assert a.hauteur() <= 2 * math.log2(n + 1)
    print(f"{nb_suites} suites, {nb_insertions} insertions : aucune règle violée")
    print()


def test_trie():
    print("#" * 60)
    print("# TEST 3 : suite triée de 1 à 2000")
    print("#" * 60)
    a = ArbreRN()
    for c in range(1, 2001):
        a.inserer(c)
        erreurs = a.verifier()
        assert not erreurs, erreurs
    borne = 2 * math.log2(2001)
    print("verifier() :", a.verifier() or "aucune règle violée")
    print(f"Hauteur = {a.hauteur()} (ABR naïf : 2000 ; borne 2*log2(n+1) = {borne:.1f})")
    print(f"Racine = {nom(a.racine)} ; cas utilisés : {a.stats}")
    print()


def test_detection():
    print("#" * 60)
    print("# TEST 4 : verifier() détecte les arbres faux")
    print("#" * 60)
    exemple = [41, 38, 31, 12, 19, 8, 50, 55]

    # Règle 2 : arbre 20(N) [10(N) [5(R)], 30(N)] puis racine peinte en rouge
    a = construire([20, 10, 30, 5])
    a.racine.couleur = ROUGE
    print("Racine 20 peinte en rouge          ->", a.verifier())

    # Règle 4 : on accroche 45 rouge sous 41 rouge, SANS réparer
    a = construire(exemple)
    n41 = a.racine.droite.gauche
    n41.droite = Noeud(45, ROUGE, n41)
    print("45 rouge accroché sous 41 rouge    ->", a.verifier())

    # Règle 5 : 41 peint en noir -> un noir de trop sur ses chemins
    a = construire(exemple)
    a.racine.droite.gauche.couleur = NOIR
    print("Nœud 41 peint en noir              ->", a.verifier())
    print()


if __name__ == "__main__":
    test_exemple()
    test_aleatoire()
    test_trie()
    test_detection()
