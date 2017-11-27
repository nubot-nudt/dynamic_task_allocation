;; Auto-generated. Do not edit!


(when (boundp 'nubot_common::WorldModelInfo)
  (if (not (find-package "NUBOT_COMMON"))
    (make-package "NUBOT_COMMON"))
  (shadow 'WorldModelInfo (find-package "NUBOT_COMMON")))
(unless (find-package "NUBOT_COMMON::WORLDMODELINFO")
  (make-package "NUBOT_COMMON::WORLDMODELINFO"))

(in-package "ROS")
;;//! \htmlinclude WorldModelInfo.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass nubot_common::WorldModelInfo
  :super ros::object
  :slots (_header _obstacleinfo _oppinfo _robotinfo _ballinfo _coachinfo ))

(defmethod nubot_common::WorldModelInfo
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:obstacleinfo __obstacleinfo) (instance nubot_common::ObstaclesInfo :init))
    ((:oppinfo __oppinfo) (instance nubot_common::ObstaclesInfo :init))
    ((:robotinfo __robotinfo) (let (r) (dotimes (i 0) (push (instance nubot_common::RobotInfo :init) r)) r))
    ((:ballinfo __ballinfo) (let (r) (dotimes (i 0) (push (instance nubot_common::BallInfo :init) r)) r))
    ((:coachinfo __coachinfo) (instance nubot_common::CoachInfo :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _obstacleinfo __obstacleinfo)
   (setq _oppinfo __oppinfo)
   (setq _robotinfo __robotinfo)
   (setq _ballinfo __ballinfo)
   (setq _coachinfo __coachinfo)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:obstacleinfo
   (&rest __obstacleinfo)
   (if (keywordp (car __obstacleinfo))
       (send* _obstacleinfo __obstacleinfo)
     (progn
       (if __obstacleinfo (setq _obstacleinfo (car __obstacleinfo)))
       _obstacleinfo)))
  (:oppinfo
   (&rest __oppinfo)
   (if (keywordp (car __oppinfo))
       (send* _oppinfo __oppinfo)
     (progn
       (if __oppinfo (setq _oppinfo (car __oppinfo)))
       _oppinfo)))
  (:robotinfo
   (&rest __robotinfo)
   (if (keywordp (car __robotinfo))
       (send* _robotinfo __robotinfo)
     (progn
       (if __robotinfo (setq _robotinfo (car __robotinfo)))
       _robotinfo)))
  (:ballinfo
   (&rest __ballinfo)
   (if (keywordp (car __ballinfo))
       (send* _ballinfo __ballinfo)
     (progn
       (if __ballinfo (setq _ballinfo (car __ballinfo)))
       _ballinfo)))
  (:coachinfo
   (&rest __coachinfo)
   (if (keywordp (car __coachinfo))
       (send* _coachinfo __coachinfo)
     (progn
       (if __coachinfo (setq _coachinfo (car __coachinfo)))
       _coachinfo)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; nubot_common/ObstaclesInfo _obstacleinfo
    (send _obstacleinfo :serialization-length)
    ;; nubot_common/ObstaclesInfo _oppinfo
    (send _oppinfo :serialization-length)
    ;; nubot_common/RobotInfo[] _robotinfo
    (apply #'+ (send-all _robotinfo :serialization-length)) 4
    ;; nubot_common/BallInfo[] _ballinfo
    (apply #'+ (send-all _ballinfo :serialization-length)) 4
    ;; nubot_common/CoachInfo _coachinfo
    (send _coachinfo :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; nubot_common/ObstaclesInfo _obstacleinfo
       (send _obstacleinfo :serialize s)
     ;; nubot_common/ObstaclesInfo _oppinfo
       (send _oppinfo :serialize s)
     ;; nubot_common/RobotInfo[] _robotinfo
     (write-long (length _robotinfo) s)
     (dolist (elem _robotinfo)
       (send elem :serialize s)
       )
     ;; nubot_common/BallInfo[] _ballinfo
     (write-long (length _ballinfo) s)
     (dolist (elem _ballinfo)
       (send elem :serialize s)
       )
     ;; nubot_common/CoachInfo _coachinfo
       (send _coachinfo :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; nubot_common/ObstaclesInfo _obstacleinfo
     (send _obstacleinfo :deserialize buf ptr-) (incf ptr- (send _obstacleinfo :serialization-length))
   ;; nubot_common/ObstaclesInfo _oppinfo
     (send _oppinfo :deserialize buf ptr-) (incf ptr- (send _oppinfo :serialization-length))
   ;; nubot_common/RobotInfo[] _robotinfo
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _robotinfo (let (r) (dotimes (i n) (push (instance nubot_common::RobotInfo :init) r)) r))
     (dolist (elem- _robotinfo)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; nubot_common/BallInfo[] _ballinfo
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _ballinfo (let (r) (dotimes (i n) (push (instance nubot_common::BallInfo :init) r)) r))
     (dolist (elem- _ballinfo)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; nubot_common/CoachInfo _coachinfo
     (send _coachinfo :deserialize buf ptr-) (incf ptr- (send _coachinfo :serialization-length))
   ;;
   self)
  )

(setf (get nubot_common::WorldModelInfo :md5sum-) "e902738e8fde937e2be378951669848c")
(setf (get nubot_common::WorldModelInfo :datatype-) "nubot_common/WorldModelInfo")
(setf (get nubot_common::WorldModelInfo :definition-)
      "Header header
ObstaclesInfo obstacleinfo
ObstaclesInfo oppinfo
RobotInfo[]   robotinfo
BallInfo[]    ballinfo
CoachInfo     coachinfo


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
MSG: nubot_common/ObstaclesInfo
Header header
Point2d[] pos
PPoint[] polar_pos


================================================================================
MSG: nubot_common/Point2d
float32 x
float32 y

================================================================================
MSG: nubot_common/PPoint
float32 angle
float32 radius

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
MSG: nubot_common/CoachInfo
Header header
char MatchMode
char MatchType
char TestMode           
Point2d pointA
Point2d pointB
int16 angleA
int16 angleB
char idA
char idB
char kickforce

")



(provide :nubot_common/WorldModelInfo "e902738e8fde937e2be378951669848c")


