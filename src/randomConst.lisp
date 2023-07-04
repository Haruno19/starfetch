;;;; Idea for starfetch contribution to improve the random number generation + added new directory to pick from
(defparameter *dirs* '(#P"/usr/local/share/starfetch/constellations/" #P"/usr/local/share/starfetch/norse-constellations/"))

;;; a bit more general. Reads from a list of directories. Returns path to file
(defun random-const ()
  (let* ((choose-dir (random (length *dirs*) (make-random-state t)))
        (choose-constellation (random
                                (length (directory (merge-pathnames (nth choose-dir *dirs*) "*.json")))
                                (make-random-state t)))
        (chosen-file (directory (merge-pathnames
                                  (nth choose-dir *dirs*)
                                  "*.json"))))
    (nth choose-constellation chosen-file)))

;;; testing the functions over a 100 times. Returns the filename
(dotimes (x 100)
  (print (pathname-name (random-const))))
