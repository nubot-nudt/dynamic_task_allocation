;; Auto-generated. Do not edit!


(when (boundp 'nubot_common::Pos2d)
  (if (not (find-package "NUBOT_COMMON"))
    (make-package "NUBOT_COMMON"))
  (shadow 'Pos2d (find-package "NUBOT_COMMON")))
(unless (find-package "NUBOT_COMMON::POS2D")
  (make-package "NUBOT_COMMON::POS2D"))

(in-package "ROS")
;;//! \htmlinclude Pos2d.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass nubot_common::Pos2d
  :super ros::object
  :slots (_header _pos ))

(defmethod nubot_common::Pos2d
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:pos __pos) (instance nubot_common::Point2d :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _pos __pos)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:pos
   (&rest __pos)
   (if (keywordp (car __pos))
       (send* _pos __pos)
     (progn
       (if __pos (setq _pos (car __pos)))
       _pos)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; nubot_common/Point2d _pos
    (send _pos :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; nubot_common/Point2d _pos
       (send _pos :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; nubot_common/Point2d _pos
     (send _pos :deserialize buf ptr-) (incf ptr- (send _pos :serialization-length))
   ;;
   self)
  )

(setf (get nubot_common::Pos2d :md5sum-) "eb6867b60acd4552a8fe8e7d015aa528")
(setf (get nubot_common::Pos2d :datatype-) "nubot_common/Pos2d")
(setf (get nubot_common::Pos2d :definition-)
      "Header header
Point2d pos


================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: nubot_common/Point2d
float32 x
float32 y

")



(provide :nubot_common/Pos2d "eb6867b60acd4552a8fe8e7d015aa528")


