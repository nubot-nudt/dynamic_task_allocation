
(cl:in-package :asdf)

(defsystem "common-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "terminal2gazebo_info" :depends-on ("_package_terminal2gazebo_info"))
    (:file "_package_terminal2gazebo_info" :depends-on ("_package"))
  ))