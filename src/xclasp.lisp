;;; Load the xclasp library

(defpackage xclasp
  (:use :common-lisp))

(in-package :xclasp)

(defun evaluate (msg)
  (format t "From Common Lisp evaluate: ~s~%" msg))

(load "/Users/meister/Development/xeus-clasp/build/libxclasp.dylib")
;;; Then use (xclasp:start-interpreter) to start the interpreter
