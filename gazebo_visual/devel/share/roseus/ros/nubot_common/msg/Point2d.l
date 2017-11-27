;; Auto-generated. Do not edit!


(when (boundp 'nubot_common::Point2d)
  (if (not (find-package "NUBOT_COMMON"))
    (make-package "NUBOT_COMMON"))
  (shadow 'Point2d (find-package "NUBOT_COMMON")))
(unless (find-package "NUBOT_COMMON::POINT2D")
  (make-package "NUBOT_COMMON::POINT2D"))

(in-package "ROS")
;;//! \htmlinclude Point2d.msg.html


(defclass nubot_common::Point2d
  :super ros::object
  :slots (_x _y ))

(defmethod nubot_common::Point2d
  (:init
   (&key
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    )
   (send-super :init)
   (setq _x (float __x))
   (setq _y (float __y))
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:serialization-length
   ()
   (+
    ;; float32 _x
    4
    ;; float32 _y
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _x
       (sys::poke _x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _y
       (sys::poke _y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _x
     (setq _x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _y
     (setq _y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get nubot_common::Point2d :md5sum-) "ff8d7d66dd3e4b731ef14a45d38888b6")
(setf (get nubot_common::Point2d :datatype-) "nubot_common/Point2d")
(setf (get nubot_common::Point2d :definition-)
      "float32 x
float32 y

")



(provide :nubot_common/Point2d "ff8d7d66dd3e4b731ef14a45d38888b6")


