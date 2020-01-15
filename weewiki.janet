(def ww-dir "_site/wiki")
(def webroot "/wiki")

(defn ref (link name)
  (org
   (string
    "[["
    (string webroot "/" link)
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
<link rel="stylesheet" href="/css/style.css">

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
