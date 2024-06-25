(def ww-dir "_site/wiki")
(def webroot "/wiki")
(def css-path 
  (if (ww-server?)
    "/css/style.css"
    (string webroot "/css/style.css")))

(defn ref (link name)
  (org
   (string
    "[["
    (string webroot "/" link)
    "]["
    name
    "]]")))

(defn html-header []
  (print
    (string/join
      @["<!DOCTYPE html>"
        "<html lang=\"en\">"
        "<head>"
        "<meta charset=\"utf-8\">"
        "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\" />"
        (string
          "<link rel=\"stylesheet\" href=\""
          css-path
          "\">")
        "</head>"
        "<body>"
        "<div id=\"main\">"] "\n")))

(defn html-footer
  []
  (print
``
</div>
</body>
</html>
``
))
