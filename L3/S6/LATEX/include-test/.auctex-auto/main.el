(TeX-add-style-hook
 "main"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("babel" "french")))
   (TeX-run-style-hooks
    "latex2e"
    "ch1"
    "ch2"
    "scrartcl"
    "scrartcl10"
    "babel"))
 :latex)

