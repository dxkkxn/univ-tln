(TeX-add-style-hook
 "main"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("babel" "french")))
   (TeX-run-style-hooks
    "latex2e"
    "scrartcl"
    "scrartcl10"
    "amsthm"
    "amssymb"
    "amsmath"
    "babel"
    "hyperref"
    "braket")
   (LaTeX-add-labels
    "eq.f")
   (LaTeX-add-environments
    "theoreme"
    "proposition"
    "corollaire"
    "lemme"
    "exo"
    "definition"))
 :latex)

