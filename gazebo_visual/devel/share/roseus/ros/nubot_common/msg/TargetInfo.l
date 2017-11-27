;; Auto-generated. Do not edit!


(when (boundp 'nubot_common::TargetInfo)
  (if (not (find-package "NUBOT_COMMON"))
    (make-package "NUBOT_COMMON"))
  (shadow 'TargetInfo (find-package "NUBOT_COMMON")))
(unless (find-package "NUBOT_COMMON::TARGETINFO")
  (make-package "NUBOT_COMMON::TARGETINFO"))

(in-package "ROS")
;;//! \htmlinclude TargetInfo.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass nubot_common::TargetInfo
  :super ros::object
  :slots (_header _target ))

(defmethod nubot_common::TargetInfo
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:target __target) (let (r) (dotimes (i 0) (push (instance nubot_common::Point2d :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _target __target)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:target
   (&rest __target)
   (if (keywordp (car __target))
       (send* _target __target)
     (progn
       (if __target (setq _target (car __target)))
       _target)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; nubot_common/Point2d[] _target
    (apply #'+ (send-all _target :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; nubot_common/Point2d[] _target
     (write-long (length _target) s)
     (dolist (elem _target)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; nubot_common/Point2d[] _target
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _target (let (r) (dotimes (i n) (push (instance nubot_common::Point2d :init) r)) r))
     (dolist (elem- _target)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get nubot_common::TargetInfo :md5sum-) "a4938944832bdc9277041fe2fa758dce")
(setf (get nubot_common::TargetInfo :datatype-) "nubot_common/TargetInfo")
(setf (get nubot_common::TargetInfo :definition-)
      "Header header
Point2d[] target

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



(provide :nubot_common/TargetInfo "a4938944832bdc9277041fe2fa758dce")


