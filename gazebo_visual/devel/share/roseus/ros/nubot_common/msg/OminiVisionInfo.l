;; Auto-generated. Do not edit!


(when (boundp 'nubot_common::OminiVisionInfo)
  (if (not (find-package "NUBOT_COMMON"))
    (make-package "NUBOT_COMMON"))
  (shadow 'OminiVisionInfo (find-package "NUBOT_COMMON")))
(unless (find-package "NUBOT_COMMON::OMINIVISIONINFO")
  (make-package "NUBOT_COMMON::OMINIVISIONINFO"))

(in-package "ROS")
;;//! \htmlinclude OminiVisionInfo.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass nubot_common::OminiVisionInfo
  :super ros::object
  :slots (_header _ballinfo _obstacleinfo _robotinfo ))

(defmethod nubot_common::OminiVisionInfo
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:ballinfo __ballinfo) (instance nubot_common::BallInfo :init))
    ((:obstacleinfo __obstacleinfo) (instance nubot_common::ObstaclesInfo :init))
    ((:robotinfo __robotinfo) (let (r) (dotimes (i 0) (push (instance nubot_common::RobotInfo :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _ballinfo __ballinfo)
   (setq _obstacleinfo __obstacleinfo)
   (setq _robotinfo __robotinfo)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:ballinfo
   (&rest __ballinfo)
   (if (keywordp (car __ballinfo))
       (send* _ballinfo __ballinfo)
     (progn
       (if __ballinfo (setq _ballinfo (car __ballinfo)))
       _ballinfo)))
  (:obstacleinfo
   (&rest __obstacleinfo)
   (if (keywordp (car __obstacleinfo))
       (send* _obstacleinfo __obstacleinfo)
     (progn
       (if __obstacleinfo (setq _obstacleinfo (car __obstacleinfo)))
       _obstacleinfo)))
  (:robotinfo
   (&rest __robotinfo)
   (if (keywordp (car __robotinfo))
       (send* _robotinfo __robotinfo)
     (progn
       (if __robotinfo (setq _robotinfo (car __robotinfo)))
       _robotinfo)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; nubot_common/BallInfo _ballinfo
    (send _ballinfo :serialization-length)
    ;; nubot_common/ObstaclesInfo _obstacleinfo
    (send _obstacleinfo :serialization-length)
    ;; nubot_common/RobotInfo[] _robotinfo
    (apply #'+ (send-all _robotinfo :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; nubot_common/BallInfo _ballinfo
       (send _ballinfo :serialize s)
     ;; nubot_common/ObstaclesInfo _obstacleinfo
       (send _obstacleinfo :serialize s)
     ;; nubot_common/RobotInfo[] _robotinfo
     (write-long (length _robotinfo) s)
     (dolist (elem _robotinfo)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; nubot_common/BallInfo _ballinfo
     (send _ballinfo :deserialize buf ptr-) (incf ptr- (send _ballinfo :serialization-length))
   ;; nubot_common/ObstaclesInfo _obstacleinfo
     (send _obstacleinfo :deserialize buf ptr-) (incf ptr- (send _obstacleinfo :serialization-length))
   ;; nubot_common/RobotInfo[] _robotinfo
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _robotinfo (let (r) (dotimes (i n) (push (instance nubot_common::RobotInfo :init) r)) r))
     (dolist (elem- _robotinfo)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get nubot_common::OminiVisionInfo :md5sum-) "18b8f1ee8d2b3404355562e6a8b63804")
(setf (get nubot_common::OminiVisionInfo :datatype-) "nubot_common/OminiVisionInfo")
(setf (get nubot_common::OminiVisionInfo :definition-)
      "Header header

BallInfo ballinfo

ObstaclesInfo obstacleinfo

RobotInfo[]  robotinfo



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
MSG: nubot_common/BallInfo
Header header
int32     ballinfostate
Point2d   pos
PPoint    real_pos
Point2d   velocity
bool      pos_known
bool      velocity_known


================================================================================
MSG: nubot_common/Point2d
float32 x
float32 y

================================================================================
MSG: nubot_common/PPoint
float32 angle
float32 radius

================================================================================
MSG: nubot_common/ObstaclesInfo
Header header
Point2d[] pos
PPoint[] polar_pos


================================================================================
MSG: nubot_common/RobotInfo
Header header
int32    AgentID
Point2d  pos
Angle    heading
float32  vrot
Point2d  vtrans
bool     iskick     
bool     isvalid 
bool     isstuck 
bool     isdribble
char     current_role
float32  role_time
Point2d  target
 

================================================================================
MSG: nubot_common/Angle
float32 theta

")



(provide :nubot_common/OminiVisionInfo "18b8f1ee8d2b3404355562e6a8b63804")


