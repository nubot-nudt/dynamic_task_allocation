;; Auto-generated. Do not edit!


(when (boundp 'nubot_common::currentCmd)
  (if (not (find-package "NUBOT_COMMON"))
    (make-package "NUBOT_COMMON"))
  (shadow 'currentCmd (find-package "NUBOT_COMMON")))
(unless (find-package "NUBOT_COMMON::CURRENTCMD")
  (make-package "NUBOT_COMMON::CURRENTCMD"))

(in-package "ROS")
;;//! \htmlinclude currentCmd.msg.html


(defclass nubot_common::currentCmd
  :super ros::object
  :slots (_current ))

(defmethod nubot_common::currentCmd
  (:init
   (&key
    ((:current __current) 0)
    )
   (send-super :init)
   (setq _current (round __current))
   self)
  (:current
   (&optional __current)
   (if __current (setq _current __current)) _current)
  (:serialization-length
   ()
   (+
    ;; int32 _current
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _current
       (write-long _current s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _current
     (setq _current (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get nubot_common::currentCmd :md5sum-) "034ddbc97d77dfabd91aa8abddfb4453")
(setf (get nubot_common::currentCmd :datatype-) "nubot_common/currentCmd")
(setf (get nubot_common::currentCmd :definition-)
      "int32 current


")



(provide :nubot_common/currentCmd "034ddbc97d77dfabd91aa8abddfb4453")


