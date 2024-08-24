(defun ftoc (fahr)
  (let ((celsius (/ (* 5 (- fahr 32)) 9))) (format t "result: ~a" celsius)))
