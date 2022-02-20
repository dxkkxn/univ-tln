(TeX-add-style-hook
 "commands"
 (lambda ()
   (TeX-run-style-hooks
    "latex2e"
    "scrartcl"
    "scrartcl10"
    "xcolor")
   (TeX-add-symbols
    '("nompropre" 2)))
 :latex)

