
(cl:in-package :asdf)

(defsystem "nubot_common-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "BallHandle" :depends-on ("_package_BallHandle"))
    (:file "_package_BallHandle" :depends-on ("_package"))
    (:file "Shoot" :depends-on ("_package_Shoot"))
    (:file "_package_Shoot" :depends-on ("_package"))
  ))