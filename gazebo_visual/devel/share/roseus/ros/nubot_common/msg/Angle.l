;; Auto-generated. Do not edit!


(when (boundp 'nubot_common::Angle)
  (if (not (find-package "NUBOT_COMMON"))
    (make-package "NUBOT_COMMON"))
  (shadow 'Angle (find-package "NUBOT_COMMON")))
(unless (find-package "NUBOT_COMMON::ANGLE")
  (make-package "NUBOT_COMMON::ANGLE"))

(in-package "ROS")
;;//! \htmlinclude Angle.msg.html


(defclass nubot_common::Angle
  :super ros::object
  :slots (_theta ))

(defmethod nubot_common::Angle
  (:init
   (&key
    ((:theta __theta) 0.0)
    )
   (send-super :init)
   (setq _theta (float __theta))
   self)
  (:theta
   (&optional __theta)
   (if __theta (setq _theta __theta)) _theta)
  (:serialization-length
   ()
   (+
    ;; float32 _theta
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _theta
       (sys::poke _theta (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _theta
     (setq _theta (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get nubot_common::Angle :md5sum-) "7328b114b91e2487fcf12e1581a80145")
(setf (get nubot_common::Angle :datatype-) "nubot_common/Angle")
(setf (get nubot_common::Angle :definition-)
      "float32 theta

")



(provide :nubot_common/Angle "7328b114b91e2487fcf12e1581a80145")


