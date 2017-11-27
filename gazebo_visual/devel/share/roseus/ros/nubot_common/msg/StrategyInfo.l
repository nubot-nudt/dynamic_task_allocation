;; Auto-generated. Do not edit!


(when (boundp 'nubot_common::StrategyInfo)
  (if (not (find-package "NUBOT_COMMON"))
    (make-package "NUBOT_COMMON"))
  (shadow 'StrategyInfo (find-package "NUBOT_COMMON")))
(unless (find-package "NUBOT_COMMON::STRATEGYINFO")
  (make-package "NUBOT_COMMON::STRATEGYINFO"))

(in-package "ROS")
;;//! \htmlinclude StrategyInfo.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass nubot_common::StrategyInfo
  :super ros::object
  :slots (_header _AgentID _targetNum1 _targetNum2 _targetNum3 _targetNum4 _staticpassNum _staticcatchNum _role _action _is_dribble _is_kickoff _role_time _pass_cmd ))

(defmethod nubot_common::StrategyInfo
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:AgentID __AgentID) 0)
    ((:targetNum1 __targetNum1) 0)
    ((:targetNum2 __targetNum2) 0)
    ((:targetNum3 __targetNum3) 0)
    ((:targetNum4 __targetNum4) 0)
    ((:staticpassNum __staticpassNum) 0)
    ((:staticcatchNum __staticcatchNum) 0)
    ((:role __role) 0)
    ((:action __action) 0)
    ((:is_dribble __is_dribble) nil)
    ((:is_kickoff __is_kickoff) nil)
    ((:role_time __role_time) 0.0)
    ((:pass_cmd __pass_cmd) (instance nubot_common::PassCommands :init))
    )
   (send-super :init)
   (setq _header __header)
   (setq _AgentID (round __AgentID))
   (setq _targetNum1 (round __targetNum1))
   (setq _targetNum2 (round __targetNum2))
   (setq _targetNum3 (round __targetNum3))
   (setq _targetNum4 (round __targetNum4))
   (setq _staticpassNum (round __staticpassNum))
   (setq _staticcatchNum (round __staticcatchNum))
   (setq _role (round __role))
   (setq _action (round __action))
   (setq _is_dribble __is_dribble)
   (setq _is_kickoff __is_kickoff)
   (setq _role_time (float __role_time))
   (setq _pass_cmd __pass_cmd)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:AgentID
   (&optional __AgentID)
   (if __AgentID (setq _AgentID __AgentID)) _AgentID)
  (:targetNum1
   (&optional __targetNum1)
   (if __targetNum1 (setq _targetNum1 __targetNum1)) _targetNum1)
  (:targetNum2
   (&optional __targetNum2)
   (if __targetNum2 (setq _targetNum2 __targetNum2)) _targetNum2)
  (:targetNum3
   (&optional __targetNum3)
   (if __targetNum3 (setq _targetNum3 __targetNum3)) _targetNum3)
  (:targetNum4
   (&optional __targetNum4)
   (if __targetNum4 (setq _targetNum4 __targetNum4)) _targetNum4)
  (:staticpassNum
   (&optional __staticpassNum)
   (if __staticpassNum (setq _staticpassNum __staticpassNum)) _staticpassNum)
  (:staticcatchNum
   (&optional __staticcatchNum)
   (if __staticcatchNum (setq _staticcatchNum __staticcatchNum)) _staticcatchNum)
  (:role
   (&optional __role)
   (if __role (setq _role __role)) _role)
  (:action
   (&optional __action)
   (if __action (setq _action __action)) _action)
  (:is_dribble
   (&optional __is_dribble)
   (if __is_dribble (setq _is_dribble __is_dribble)) _is_dribble)
  (:is_kickoff
   (&optional __is_kickoff)
   (if __is_kickoff (setq _is_kickoff __is_kickoff)) _is_kickoff)
  (:role_time
   (&optional __role_time)
   (if __role_time (setq _role_time __role_time)) _role_time)
  (:pass_cmd
   (&rest __pass_cmd)
   (if (keywordp (car __pass_cmd))
       (send* _pass_cmd __pass_cmd)
     (progn
       (if __pass_cmd (setq _pass_cmd (car __pass_cmd)))
       _pass_cmd)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; int32 _AgentID
    4
    ;; int32 _targetNum1
    4
    ;; int32 _targetNum2
    4
    ;; int32 _targetNum3
    4
    ;; int32 _targetNum4
    4
    ;; int32 _staticpassNum
    4
    ;; int32 _staticcatchNum
    4
    ;; uint32 _role
    4
    ;; uint32 _action
    4
    ;; bool _is_dribble
    1
    ;; bool _is_kickoff
    1
    ;; float32 _role_time
    4
    ;; nubot_common/PassCommands _pass_cmd
    (send _pass_cmd :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; int32 _AgentID
       (write-long _AgentID s)
     ;; int32 _targetNum1
       (write-long _targetNum1 s)
     ;; int32 _targetNum2
       (write-long _targetNum2 s)
     ;; int32 _targetNum3
       (write-long _targetNum3 s)
     ;; int32 _targetNum4
       (write-long _targetNum4 s)
     ;; int32 _staticpassNum
       (write-long _staticpassNum s)
     ;; int32 _staticcatchNum
       (write-long _staticcatchNum s)
     ;; uint32 _role
       (write-long _role s)
     ;; uint32 _action
       (write-long _action s)
     ;; bool _is_dribble
       (if _is_dribble (write-byte -1 s) (write-byte 0 s))
     ;; bool _is_kickoff
       (if _is_kickoff (write-byte -1 s) (write-byte 0 s))
     ;; float32 _role_time
       (sys::poke _role_time (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; nubot_common/PassCommands _pass_cmd
       (send _pass_cmd :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; int32 _AgentID
     (setq _AgentID (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _targetNum1
     (setq _targetNum1 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _targetNum2
     (setq _targetNum2 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _targetNum3
     (setq _targetNum3 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _targetNum4
     (setq _targetNum4 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _staticpassNum
     (setq _staticpassNum (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _staticcatchNum
     (setq _staticcatchNum (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _role
     (setq _role (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _action
     (setq _action (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; bool _is_dribble
     (setq _is_dribble (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _is_kickoff
     (setq _is_kickoff (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; float32 _role_time
     (setq _role_time (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; nubot_common/PassCommands _pass_cmd
     (send _pass_cmd :deserialize buf ptr-) (incf ptr- (send _pass_cmd :serialization-length))
   ;;
   self)
  )

(setf (get nubot_common::StrategyInfo :md5sum-) "9983cea3e357670f055f12d4322a06c9")
(setf (get nubot_common::StrategyInfo :datatype-) "nubot_common/StrategyInfo")
(setf (get nubot_common::StrategyInfo :definition-)
      "Header   header
int32    AgentID
int32    targetNum1
int32    targetNum2
int32    targetNum3
int32    targetNum4
int32    staticpassNum
int32    staticcatchNum
uint32   role
uint32   action
bool     is_dribble
bool     is_kickoff
float32  role_time
PassCommands  pass_cmd




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
MSG: nubot_common/PassCommands
uint32  pass_id
uint32  catch_id
Point2d pass_pt
Point2d catch_pt
bool    is_passout
bool    is_dynamic_pass
bool    is_static_pass
bool    is_valid
 

================================================================================
MSG: nubot_common/Point2d
float32 x
float32 y

")



(provide :nubot_common/StrategyInfo "9983cea3e357670f055f12d4322a06c9")


