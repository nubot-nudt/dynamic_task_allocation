;; Auto-generated. Do not edit!


(when (boundp 'nubot_common::MotorInfo)
  (if (not (find-package "NUBOT_COMMON"))
    (make-package "NUBOT_COMMON"))
  (shadow 'MotorInfo (find-package "NUBOT_COMMON")))
(unless (find-package "NUBOT_COMMON::MOTORINFO")
  (make-package "NUBOT_COMMON::MOTORINFO"))

(in-package "ROS")
;;//! \htmlinclude MotorInfo.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass nubot_common::MotorInfo
  :super ros::object
  :slots (_header _motordata ))

(defmethod nubot_common::MotorInfo
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:motordata __motordata) (make-array 4 :initial-element 0 :element-type :integer))
    )
   (send-super :init)
   (setq _header __header)
   (setq _motordata __motordata)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:motordata
   (&optional __motordata)
   (if __motordata (setq _motordata __motordata)) _motordata)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; uint32[4] _motordata
    (* 4    4)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; uint32[4] _motordata
     (dotimes (i 4)
       (write-long (elt _motordata i) s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; uint32[4] _motordata
   (dotimes (i (length _motordata))
     (setf (elt _motordata i) (sys::peek buf ptr- :integer)) (incf ptr- 4)
     )
   ;;
   self)
  )

(setf (get nubot_common::MotorInfo :md5sum-) "a75d984a29f54312561eb327c067e655")
(setf (get nubot_common::MotorInfo :datatype-) "nubot_common/MotorInfo")
(setf (get nubot_common::MotorInfo :definition-)
      "Header header
uint32[4] motordata


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

")



(provide :nubot_common/MotorInfo "a75d984a29f54312561eb327c067e655")


