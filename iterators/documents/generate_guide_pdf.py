import subprocess
from pathlib import Path

html_content = """<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <title>Comprendre en Profondeur std::vector et les Itérateurs en C++</title>
    <style>
        @page {
            size: A4;
            margin: 18mm 16mm 20mm 16mm;
            @bottom-right {
                content: counter(page) " / " counter(pages);
                font-size: 9pt;
                color: #64748b;
            }
        }
        
        * {
            box-sizing: border-box;
        }

        body {
            font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif;
            font-size: 10.5pt;
            line-height: 1.6;
            color: #1e293b;
            background: #ffffff;
            margin: 0;
            padding: 0;
        }

        h1, h2, h3, h4 {
            color: #0f172a;
            font-weight: 700;
            margin-top: 1.4em;
            margin-bottom: 0.5em;
            line-height: 1.25;
        }

        h1 {
            font-size: 22pt;
            text-align: center;
            color: #1e3a8a;
            border-bottom: 3px solid #3b82f6;
            padding-bottom: 12px;
            margin-top: 0;
            margin-bottom: 25px;
        }

        .subtitle {
            text-align: center;
            font-size: 12pt;
            color: #475569;
            margin-top: -15px;
            margin-bottom: 30px;
            font-style: italic;
        }

        h2 {
            font-size: 14pt;
            border-left: 5px solid #2563eb;
            padding-left: 10px;
            background: #eff6ff;
            padding-top: 6px;
            padding-bottom: 6px;
            border-radius: 0 4px 4px 0;
            page-break-after: avoid;
        }

        h3 {
            font-size: 12pt;
            color: #1d4ed8;
            margin-top: 1.1em;
            page-break-after: avoid;
        }

        p, ul, ol {
            margin-top: 0.4em;
            margin-bottom: 0.8em;
        }

        ul, ol {
            padding-left: 22px;
        }

        li {
            margin-bottom: 4px;
        }

        code {
            font-family: "JetBrainsMono Nerd Font", "JetBrains Mono", "Fira Code", Consolas, monospace;
            font-size: 9.5pt;
            background-color: #f1f5f9;
            color: #b91c1c;
            padding: 2px 5px;
            border-radius: 4px;
            border: 1px solid #e2e8f0;
        }

        pre {
            background-color: #0f172a;
            color: #f8fafc;
            padding: 12px 14px;
            border-radius: 6px;
            font-family: "JetBrainsMono Nerd Font", "JetBrains Mono", Consolas, monospace;
            font-size: 9pt;
            line-height: 1.45;
            overflow-x: auto;
            border: 1px solid #1e293b;
            page-break-inside: avoid;
            margin: 10px 0 16px 0;
        }

        pre code {
            background: none;
            color: inherit;
            border: none;
            padding: 0;
            font-size: inherit;
        }

        .kw { color: #f43f5e; font-weight: bold; } /* keyword */
        .type { color: #38bdf8; } /* type */
        .str { color: #a3e635; } /* string */
        .com { color: #64748b; font-style: italic; } /* comment */
        .fn { color: #fbbf24; } /* function */
        .num { color: #c084fc; } /* number */

        .box {
            border-radius: 6px;
            padding: 12px 16px;
            margin: 14px 0;
            page-break-inside: avoid;
        }

        .box-info {
            background-color: #f0fdf4;
            border: 1px solid #bbf7d0;
            border-left: 5px solid #16a34a;
        }

        .box-warn {
            background-color: #fffbeb;
            border: 1px solid #fef3c7;
            border-left: 5px solid #d97706;
        }

        .box-title {
            font-weight: bold;
            margin-bottom: 4px;
            display: flex;
            align-items: center;
            gap: 6px;
        }

        .diagram {
            background-color: #f8fafc;
            border: 1px solid #cbd5e1;
            border-radius: 6px;
            padding: 14px;
            margin: 14px 0;
            font-family: "JetBrainsMono Nerd Font", monospace;
            font-size: 9pt;
            line-height: 1.4;
            page-break-inside: avoid;
            white-space: pre;
            overflow-x: auto;
        }

        table {
            width: 100%;
            border-collapse: collapse;
            margin: 14px 0;
            font-size: 9.5pt;
            page-break-inside: avoid;
        }

        th, td {
            border: 1px solid #cbd5e1;
            padding: 7px 10px;
            text-align: left;
        }

        th {
            background-color: #f1f5f9;
            color: #0f172a;
            font-weight: 600;
        }

        tr:nth-child(even) {
            background-color: #f8fafc;
        }

        .page-break {
            page-break-before: always;
        }
    </style>
</head>
<body>

    <h1>std::vector &amp; les Itérateurs en C++</h1>
    <div class="subtitle">Architecture interne, Design Pattern Iterator, mémoire et cas pratiques</div>

    <h2>1. Philosophie : Pourquoi les Itérateurs ? (Design Pattern Iterator)</h2>
    <p>
        Dans la bibliothèque standard (STL) conçue par <strong>Alexander Stepanov</strong>, l'objectif fondamental était de résoudre le problème d'explosion combinatoire entre <em>conteneurs</em> et <em>algorithmes</em> :
    </p>
    <ul>
        <li>Si vous avez <strong>N conteneurs</strong> (vector, list, deque, set...) et <strong>M algorithmes</strong> (find, sort, count, copy...), sans abstraction, il faudrait écrire <code>N &times; M</code> fonctions distinctes.</li>
        <li><strong>La solution de la STL :</strong> Insérer un pont universel : <strong>l'itérateur</strong>. Les algorithmes ne manipulent jamais directement le conteneur, ils manipulent uniquement une paire d'itérateurs <code>[first, last)</code>.</li>
    </ul>

    <div class="diagram">
+---------------------+                      +---------------------+
|   Conteneurs STL    |                      |  Algorithmes STL    |
| (vector, list, set) |                      | (find, sort, copy)  |
+----------+----------+                      +----------+----------+
           |                                            |
           +---------------->[ ITÉRATEURS ]<------------+
                       (Interface d'accès standard)
    </div>

    <div class="box box-info">
        <div class="box-title">&#128161; Définition Formelle</div>
        Un itérateur est une généralisation du concept de <strong>pointeur</strong>. C'est un objet (ou un pointeur brut) qui permet de parcourir les éléments d'une séquence et d'accéder à leur valeur via la surcharge des opérateurs : <code>*it</code>, <code>it++</code>, <code>it != end</code>, <code>it-&gt;member</code>.
    </div>

    <h2>2. Anatomie Interne de <code>std::vector</code></h2>
    <p>
        Contrairement aux tableaux statiques C (<code>int tab[10]</code>) ou aux listes chaînées (<code>std::list</code>), <code>std::vector</code> est un <strong>tableau dynamique contigu en mémoire</strong>.
    </p>

    <h3>Structure en mémoire (Stack vs Heap)</h3>
    <p>Sur la pile (Stack), un objet <code>std::vector</code> n'occupe que <strong>24 octets</strong> (sur architecture 64 bits), constitués de 3 pointeurs bruts :</p>
    <ul>
        <li><code>_M_start</code> : pointe sur le 1er élément alloué sur le tas.</li>
        <li><code>_M_finish</code> : pointe juste après le dernier élément valide (correspond à <code>end()</code>).</li>
        <li><code>_M_end_of_storage</code> : pointe sur la fin du bloc mémoire actuellement réservé.</li>
    </ul>

    <div class="diagram">
STACK (Objet vector, 24 octets) :
+-----------------+-----------------+---------------------+
|    _M_start     |   _M_finish     | _M_end_of_storage   |
+--------+--------+--------+--------+----------+----------+
         |                 |                   |
HEAP (Mémoire allouée en continu) :            |
         v                 v                   v
        [ 10 | 20 | 30 | 40 | ? | ? | ? | ? ]  |
        |<--- size = 4 ---->|                  |
        |<------------- capacity = 8 --------->|
    </div>

    <h3>Différence Cruciale : <code>size()</code> vs <code>capacity()</code></h3>
    <table>
        <thead>
            <tr>
                <th>Propriété</th>
                <th>Méthode</th>
                <th>Définition</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td><strong>Taille (Size)</strong></td>
                <td><code>vec.size()</code></td>
                <td>Nombre d'éléments réels actuellement construits (<code>_M_finish - _M_start</code>).</td>
            </tr>
            <tr>
                <td><strong>Capacité (Capacity)</strong></td>
                <td><code>vec.capacity()</code></td>
                <td>Nombre total d'éléments que le vector peut contenir avant d'avoir à réallouer la mémoire (<code>_M_end_of_storage - _M_start</code>).</td>
            </tr>
        </tbody>
    </table>

    <div class="page-break"></div>

    <h3>La Réallocation Dynamique &amp; Coût Amorti &#120490;(1)</h3>
    <p>
        Quand <code>size() == capacity()</code> et qu'on effectue un <code>push_back()</code> :
    </p>
    <ol>
        <li>Le vector alloue un <strong>nouveau bloc</strong> plus grand ailleurs sur le tas (généralement le double : facteur 2 en GCC/Clang, 1.5 en MSVC).</li>
        <li>Il <strong>déplace (move)</strong> ou copie les anciens éléments vers la nouvelle zone mémoire.</li>
        <li>Il détruit les anciens éléments et libère l'ancienne mémoire.</li>
        <li>Il ajoute le nouvel élément.</li>
    </ol>

    <div class="box box-warn">
        <div class="box-title">&#9888; Danger : Invalidation des Itérateurs !</div>
        Lors d'une réallocation, l'ancien bloc mémoire est désalloué ! Tout pointeur, référence ou itérateur pointant sur l'ancien bloc devient un <strong>dangling pointer</strong> (pointeur sauvage). L'accès à cet itérateur provoque un <em>Undefined Behavior</em> (crash ou corruption mémoire).
        <br><br>
        <strong>Bonne pratique :</strong> Si vous connaissez à l'avance le nombre d'éléments, utilisez <code>vec.reserve(N)</code> pour éviter les réallocations inutiles.
    </div>

    <h2>3. La Hiérarchie des Catégories d'Itérateurs</h2>
    <p>Tous les itérateurs ne permettent pas les mêmes opérations. Le C++ définit des catégories précises :</p>

    <table>
        <thead>
            <tr>
                <th>Catégorie</th>
                <th>Opérations permises</th>
                <th>Exemple de conteneur / source</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td><strong>Input</strong></td>
                <td>Lecture seule, 1 seul passage séquentiel (<code>*it</code>, <code>++it</code>)</td>
                <td><code>std::istream_iterator</code></td>
            </tr>
            <tr>
                <td><strong>Output</strong></td>
                <td>Écriture seule, 1 seul passage (<code>*it = val</code>, <code>++it</code>)</td>
                <td><code>std::ostream_iterator</code>, <code>std::back_inserter</code></td>
            </tr>
            <tr>
                <td><strong>Forward</strong></td>
                <td>Lecture/Écriture, passages multiples vers l'avant</td>
                <td><code>std::forward_list</code> (liste simplement chaînée)</td>
            </tr>
            <tr>
                <td><strong>Bidirectional</strong></td>
                <td>Vers l'avant et vers l'arrière (<code>++it</code>, <code>--it</code>)</td>
                <td><code>std::list</code>, <code>std::set</code>, <code>std::map</code></td>
            </tr>
            <tr>
                <td><strong>Random Access</strong></td>
                <td>Saut direct en temps constant &#120490;(1) (<code>it + n</code>, <code>it[n]</code>, <code>it1 &lt; it2</code>)</td>
                <td><code>std::deque</code></td>
            </tr>
            <tr>
                <td><strong>Contiguous</strong></td>
                <td>Random Access + éléments physiquement adjacents en mémoire</td>
                <td><code>std::vector</code>, <code>std::array</code>, <code>std::string</code>, pointeur brut <code>T*</code></td>
            </tr>
        </tbody>
    </table>

    <h2>4. Les 4 Types d'Itérateurs d'un Vector</h2>
    <p>Pour un conteneur <code>std::vector&lt;T&gt;</code>, il existe 4 types de parcours :</p>
    <ul>
        <li><code>vector&lt;T&gt;::iterator</code> : Début avec <code>begin()</code>, fin avec <code>end()</code> (modifiable).</li>
        <li><code>vector&lt;T&gt;::const_iterator</code> : Début avec <code>cbegin()</code>, fin avec <code>cend()</code> (lecture seule).</li>
        <li><code>vector&lt;T&gt;::reverse_iterator</code> : Début avec <code>rbegin()</code>, fin avec <code>rend()</code> (parcours inversé).</li>
        <li><code>vector&lt;T&gt;::const_reverse_iterator</code> : Début avec <code>crbegin()</code>, fin avec <code>crend()</code> (parcours inversé lecture seule).</li>
    </ul>

    <div class="box box-info">
        <div class="box-title">&#128273; Convention Fondamentale STL : L'intervalle semi-ouvert [begin, end)</div>
        <code>end()</code> et <code>rend()</code> ne pointent <strong>JAMAIS</strong> sur un élément valide ! Ils pointent sur la position fictive « <em>un cran après le dernier élément</em> ». C'est ce qui permet d'écrire la condition d'arrêt : <code>it != vec.end()</code>.
    </div>

    <div class="page-break"></div>

    <h2>5. Analyse Détaillée de votre Code (L'Énigme du Reverse Iterator)</h2>
    <p>
        Dans votre code <code>example1.cpp</code>, vous avez observé :
    </p>

    <pre><code><span class="type">vector</span>&lt;<span class="type">int</span>&gt; coll = {<span class="num">1</span>, <span class="num">2</span>, <span class="num">3</span>, <span class="num">4</span>, <span class="num">5</span>, <span class="num">6</span>, <span class="num">7</span>, <span class="num">8</span>, <span class="num">9</span>};
<span class="keyword">auto</span> pos = <span class="fn">find</span>(coll.cbegin(), coll.cend(), <span class="num">5</span>); <span class="com">// pos pointe sur 5</span>
<span class="type">vector</span>&lt;<span class="type">int</span>&gt;::<span class="type">const_reverse_iterator</span> <span class="fn">rpos</span>(pos);

cout &lt;&lt; <span class="str">"*pos: "</span> &lt;&lt; *pos &lt;&lt; endl;   <span class="com">// Affiche 5</span>
cout &lt;&lt; <span class="str">"*rpos: "</span> &lt;&lt; *rpos &lt;&lt; endl; <span class="com">// Affiche 4 ! Pourquoi ?!</span></code></pre>

    <h3>Pourquoi <code>*rpos</code> donne-t-il 4 ?</h3>
    <p>
        Pour comprendre ce comportement, il faut observer comment <code>rbegin()</code> et <code>rend()</code> sont définis par rapport à <code>begin()</code> et <code>end()</code> :
    </p>

    <div class="diagram">
Index :           0      1      2      3      4      5      6      7      8
Éléments :     [  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  ]   (hors borne)
                  ^                           ^                           ^
                  |                           |                           |
               begin()                       pos                        end()
                                            rpos.base()
                                      &lt;-------+ (décalage de 1 en arrière)
                                       *rpos lit ici : 4
                                              ^
                                              |
               rend().base()               rbegin().base()
    </div>

    <h3>La Relation Mathématique STL :</h3>
    <p>
        Pour qu'un <code>reverse_iterator</code> puisse parcourir toute la collection de droite à gauche en respectant la convention semi-ouverte :
    </p>
    <ul>
        <li><code>rbegin()</code> est construit à partir de <code>end()</code>.</li>
        <li><code>rend()</code> est construit à partir de <code>begin()</code>.</li>
        <li>Quand on déréférence <code>*rpos</code>, la STL exécute : <code>*(rpos.base() - 1)</code>.</li>
    </ul>
    <p>
        Puisque <code>rpos</code> a été initialisé avec <code>pos</code> (qui pointe sur 5), son <code>base()</code> est <code>pos</code>. Donc déréférencer <code>*rpos</code> renvoie l'élément situé juste <strong>avant</strong> <code>pos</code>, c'est-à-dire <strong>4</strong> !
    </p>

    <h2>6. Pièges Fréquents &amp; Bonnes Pratiques</h2>

    <h3>Piège n°1 : Invalidation d'itérateur lors d'une suppression</h3>
    <pre><code><span class="com">// ERREUR GRAVE : it est invalidé dès que erase() est appelé !</span>
<span class="kw">for</span> (<span class="kw">auto</span> it = vec.begin(); it != vec.end(); ++it) {
    <span class="kw">if</span> (*it == <span class="num">5</span>) {
        vec.<span class="fn">erase</span>(it); <span class="com">// CRASH ou Undefined Behavior au prochain ++it !</span>
    }
}

<span class="com">// LA BONNE MÉTHODE (C++98 / C++11) : erase() retourne le prochain itérateur valide</span>
<span class="kw">for</span> (<span class="kw">auto</span> it = vec.begin(); it != vec.end(); ) {
    <span class="kw">if</span> (*it == <span class="num">5</span>) {
        it = vec.<span class="fn">erase</span>(it); <span class="com">// mise à jour propre de it</span>
    } <span class="kw">else</span> {
        ++it;
    }
}

<span class="com">// LA MÉTHODE MODERNE (C++20) : std::erase</span>
std::<span class="fn">erase</span>(vec, <span class="num">5</span>);</code></pre>

    <div class="box box-info">
        <div class="box-title">&#10004; Synthèse des Règles d'Or</div>
        <ol>
            <li>Préférez <code>cbegin()</code> / <code>cend()</code> si vous n'avez pas besoin de modifier l'élément.</li>
            <li>Préférez les boucles par intervalle (Range-based for) <code>for (const auto&amp; x : vec)</code> quand vous n'avez pas besoin de l'indice ou de l'itérateur.</li>
            <li>Utilisez <code>std::reserve()</code> avant d'insérer beaucoup d'éléments avec <code>push_back()</code>.</li>
            <li>Ne stockez jamais un itérateur à travers des opérations qui modifient la taille du vecteur (<code>push_back</code>, <code>insert</code>, <code>erase</code>, <code>resize</code>).</li>
        </ol>
    </div>

</body>
</html>
"""

html_path = Path("/tmp/guide_vector_iterators.html")
html_path.write_text(html_content, encoding="utf-8")

script_dir = Path(__file__).resolve().parent
pdf_path = script_dir / "Guide_Complet_Vector_et_Iterateurs.pdf"

cmd = [
    "google-chrome",
    "--headless",
    "--disable-gpu",
    "--no-sandbox",
    "--no-pdf-header-footer",
    f"--print-to-pdf={pdf_path}",
    f"file://{html_path}"
]

print("Génération du PDF...")
res = subprocess.run(cmd, capture_output=True, text=True)
if res.returncode == 0:
    print(f"PDF généré avec succès : {pdf_path}")
else:
    print("Erreur:", res.stderr)
