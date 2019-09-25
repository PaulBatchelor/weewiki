(def ww-dir "_site/wiki")

(defn ref (link name)
  (org
   (string
    "[["
    (string ww-dir "/" link ".html")
    "]["
    name
    "]]")))

(defn html-header
  []
(print
``<!DOCTYPE html>
<html lang="en">
<head>

<meta charset="utf-8">
<link rel="stylesheet" href="style.css">

</head>
<body>
<div id="main">
``)
)

(defn html-footer
  []
  (print
``
</div>
</body>
</html>
``
))
