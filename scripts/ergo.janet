(def hexergokey "asdfhjklqweruiop")

(defn hex-to-ergo [str]
  (var e @[])
  (def ch0 ((string/bytes "0") 0))
  (def ch9 ((string/bytes "9") 0))
  (def cha ((string/bytes "a") 0))
  (def chf ((string/bytes "f") 0))

  (each s str
    (do
      (var pos -1)
      (if (and (>= s ch0) (<= ch9))
        (set pos (- s ch0)))
      (if (and (>= s cha) (<= chf))
        (set pos (+ (- s cha) 10)))
      (if (>= pos 0)
        (array/push e (hexergokey pos))
        (array/push e s))))
  (string/from-bytes (splice e)))

(defn mini [uuid]
 (string
  "g" (hex-to-ergo (string/slice uuid 0 8))))
