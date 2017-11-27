;; Auto-generated. Do not edit!


(when (boundp 'nubot_common::FrontBallInfo)
  (if (not (find-package "NUBOT_COMMON"))
    (make-package "NUBOT_COMMON"))
  (shadow 'FrontBallInfo (find-package "NUBOT_COMMON")))
(unless (find-package "NUBOT_COMMON::FRONTBALLINFO")
  (make-package "NUBOT_COMMON::FRONTBALLINFO"))

(in-package "ROS")
;;//! \htmlinclude FrontBallInfo.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass nubot_common::FrontBallInfo
  :super ros::object
  :slots (_header _real_pos _pos_known ))

(defmethod nubot_common::FrontBallInfo
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:real_pos __real_pos) (instance nubot_common::PPoint :init))
    ((:pos_known __pos_known) nil)
    )
   (send-super :init)
   (setq _header __header)
   (setq _real_pos __real_pos)
   (setq _pos_known __pos_known)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:real_pos
   (&rest __real_pos)
   (if (keywordp (car __real_pos))
       (send* _real_pos __real_pos)
     (progn
       (if __real_pos (setq _real_pos (car __real_pos)))
       _real_pos)))
  (:pos_known
   (&optional __pos_known)
   (if __pos_known (setq _pos_known __pos_known)) _pos_known)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; nubot_common/PPoint _real_pos
    (send _real_pos :serialization-length)
    ;; bool _pos_known
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; nubot_common/PPoint _real_pos
       (send _real_pos :serialize s)
     ;; bool _pos_known
       (if _pos_known (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; nubot_common/PPoint _real_pos
     (send _real_pos :deserialize buf ptr-) (incf ptr- (send _real_pos :serialization-length))
   ;; bool _pos_known
     (setq _pos_known (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get nubot_common::FrontBallInfo :md5sum-) "2f6f5be4b3c5cce090957cd65810f7ac")
(setf (get nubot_common::FrontBallInfo :datatype-) "nubot_common/FrontBallInfo")
(setf (get nubot_common::FrontBallInfo :definition-)
      "Header header
PPoint real_pos
bool   pos_known
 


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
MSG: nubot_common/PPoint
float32 angle
float32 radius

")



(provide :nubot_common/FrontBallInfo "2f6f5be4b3c5cce090957cd65810f7ac")


