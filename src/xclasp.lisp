;;; Load the xclasp library

(defpackage xclasp
  (:use :common-lisp))

(in-package :xclasp)

(defun evaluate (msg)
  (let ((expr (read-from-string msg)))
    (eval expr)))

(load "/Users/kevin/Development/xeus-clasp/libxclasp.dylib")
;;; Then use (xclasp:start-interpreter) to start the interpreter

(xclasp:start-interpreter (elt core:*command-line-arguments* 0))
