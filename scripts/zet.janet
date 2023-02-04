(defn html-escape (str)
  # make sure mentions appear
  (string/replace-all
   "@<" "@&lt;"
   (string/replace-all "txt>" "txt&gt;" str)))


(def valid-pgname
  '{:letter (range "az" "AZ")
    :number (range "09")
    :word (any (choice :letter (set "_") :number))
    :everything (any (choice 1))
    :main (sequence (capture :word) (capture :everything))})

(defn mklink [word]
  (def name (peg/match valid-pgname (string/slice word 1 -1)))
  (string "(" (refstr (name 0)) ")" (name 1)))

(defn fmtmsg [msg]
  (var words (string/split " " (html-escape msg)))
  (for w 0 (length words)
    (if (and
          (> (length (words w)) 0)
          (= ((words w) 0)
             ((string/bytes "!") 0)))
      (set (words w)
           (mklink (words w)))))
  (string/join words " "))


(def valid-pgname
  '{:letter (range "az" "AZ")
    :number (range "09")
    :word (any (choice :letter (set "_") :number))
    :everything (any (choice 1))
    :main (sequence (capture :word) (capture :everything))})

(defn mklink [word]
  (def name (peg/match valid-pgname (string/slice word 1 -1)))
  (string "(" (refstr (name 0)) ")" (name 1)))

(defn fmtmsg [msg]
  (var words (string/split " " (html-escape msg)))
  (for w 0 (length words)
    (if (and (> (length (words w)) 1)
             (= ((words w) 0) ((string/bytes "!") 0)))
      (set (words w)
           (mklink (words w)))))
  (string/join words " "))
(defn print-value [uuid]
  (def vals
    (sqlite3/eval
     (ww-db)
     (string "SELECT time, value, "
             "strftime('%s', time) as secs from wikizet "
             "WHERE UUID is \"" uuid
             "\" AND value like \">%\""
             "ORDER by secs DESC;")))

  (each v vals
    (org (string (v "time") ":\n\n"))
    (org (string (string/slice (v "value") 1 -1) "\n\n"))))

(defn refstr [uuid]
  (def query (sqlite3/eval
          (ww-db)
          (string
           "SELECT value FROM wikizet WHERE "
           "UUID IS '" uuid "' AND value LIKE '#%';")))

  (var str @[])
  (each v query
    (array/push str (string/slice (v "value") 1 9)))

  (string/join str ", "))

(defn messages [group &opt typeflag genrefs limit]
  (default typeflag "@")
  (default genrefs false)
  (def gid
       (((sqlite3/eval
        (ww-db)
        (string
         "SELECT UUID FROM wikizet where "
         "value is \"" typeflag group "\";")) 0) "UUID"))

  (if genrefs
    (sqlite3/eval
     (ww-db)
     (string
      "CREATE TEMPORARY VIEW trefs as "
      "SELECT UUID as id, value as ref from wikizet "
      "where value like '#%';")))

  (def addr
    (sqlite3/eval
     (ww-db)
     (string
      "SELECT "
      "strftime('%Y-%m-%d-%H-%M', time, 'localtime') as time, "
      "value, "
      "substr(UUID, 1, 8) as UUID "
      (if genrefs
        (string
         ", GROUP_CONCAT(substr(ref, 2, 8)) as refstr "))
      "FROM wikizet "
      (if genrefs
        (string
         "INNER JOIN trefs "
         "on wikizet.UUID = trefs.ID "))
      "where UUID IN ("
      "SELECT UUID from wikizet WHERE value is '#"
      gid "') and VALUE like '>%' "
      (if genrefs "GROUP by UUID ")
      "ORDER by strftime('%s', time) DESC "
      (if limit (string "LIMIT " limit))
      ";"
)))

  (each id addr
    (org (string "*"
                 (string
                  "[" (string/slice (id "UUID") 0 8) "] ")
                 (id "time")
                 "*: "))
    (org (string
          (fmtmsg (string/slice (id "value") 1 -1))
          "\n\n"))
    (if genrefs
      (org (string "references: " (id "refstr") "\n\n"))))

  (if genrefs
    (sqlite3/eval (ww-db) (string "DROP VIEW trefs"))))

(defn page-updates [] (messages (ww-name) "!"))

(defn uuid [str]
  (org
   (string "=g"
           (ergo/hex-to-ergo (ww-zet-resolve str))
           "=")))

(defn page-amalg [group]
  (def group-uuid (ww-zet-resolve (string "@" group)))
  (def querystr (string/format
                 `SELECT GROUP_CONCAT(value, "__") as vals from
wikizet
where UUID in(
SELECT wikizet.UUID FROM wikizet
WHERE
wikizet.value IS '#' || '%s'
)
and (value like "!%%" or
value like "$blurb:%%")
GROUP BY wikizet.UUID
ORDER BY value ASC
;` group-uuid))

  (def rows (sqlite3/eval (ww-db) querystr))

  (each r rows
    (def vals (string/split "__" (r "vals")))
    (if (= (length vals) 1)
      (do
        (def page (string/slice (vals 0) 1))
        (ref page)
        (org "\n"))
      (do
        (def page (string/slice (vals 0) 1))
        (def blurb (string/slice (vals 1) (length "$blurb:>")))
        (ref page)
        (org ": ")
        (org (fmtmsg blurb))
        (org "\n")))))
