;; Auto-generated. Do not edit!


(when (boundp 'nubot_common::ObstaclesInfo)
  (if (not (find-package "NUBOT_COMMON"))
    (make-package "NUBOT_COMMON"))
  (shadow 'ObstaclesInfo (find-package "NUBOT_COMMON")))
(unless (find-package "NUBOT_COMMON::OBSTACLESINFO")
  (make-package "NUBOT_COMMON::OBSTACLESINFO"))

(in-package "ROS")
;;//! \htmlinclude ObstaclesInfo.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass nubot_common::ObstaclesInfo
  :super ros::object
  :slots (_header _pos _polar_pos ))

(defmethod nubot_common::ObstaclesInfo
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:pos __pos) (let (r) (dotimes (i 0) (push (instance nubot_common::Point2d :init) r)) r))
    ((:polar_pos __polar_pos) (let (r) (dotimes (i 0) (push (instance nubot_common::PPoint :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _pos __pos)
   (setq _polar_pos __polar_pos)
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
  (:polar_pos
   (&rest __polar_pos)
   (if (keywordp (car __polar_pos))
       (send* _polar_pos __polar_pos)
     (progn
       (if __polar_pos (setq _polar_pos (car __polar_pos)))
       _polar_pos)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; nubot_common/Point2d[] _pos
    (apply #'+ (send-all _pos :serialization-length)) 4
    ;; nubot_common/PPoint[] _polar_pos
    (apply #'+ (send-all _polar_pos :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; nubot_common/Point2d[] _pos
     (write-long (length _pos) s)
     (dolist (elem _pos)
       (send elem :serialize s)
       )
     ;; nubot_common/PPoint[] _polar_pos
     (write-long (length _polar_pos) s)
     (dolist (elem _polar_pos)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; nubot_common/Point2d[] _pos
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _pos (let (r) (dotimes (i n) (push (instance nubot_common::Point2d :init) r)) r))
     (dolist (elem- _pos)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; nubot_common/PPoint[] _polar_pos
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _polar_pos (let (r) (dotimes (i n) (push (instance nubot_common::PPoint :init) r)) r))
     (dolist (elem- _polar_pos)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get nubot_common::ObstaclesInfo :md5sum-) "8850a2241dd98578d2d66d842f5946c8")
(setf (get nubot_common::ObstaclesInfo :datatype-) "nubot_common/ObstaclesInfo")
(setf (get nubot_common::ObstaclesInfo :definition-)
      "Header header
Point2d[] pos
PPoint[] polar_pos


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

================================================================================
MSG: nubot_common/PPoint
float32 angle
float32 radius

")



(provide :nubot_common/ObstaclesInfo "8850a2241dd98578d2d66d842f5946c8")


