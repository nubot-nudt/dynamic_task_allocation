;; Auto-generated. Do not edit!


(when (boundp 'nubot_common::simulation_strategy)
  (if (not (find-package "NUBOT_COMMON"))
    (make-package "NUBOT_COMMON"))
  (shadow 'simulation_strategy (find-package "NUBOT_COMMON")))
(unless (find-package "NUBOT_COMMON::SIMULATION_STRATEGY")
  (make-package "NUBOT_COMMON::SIMULATION_STRATEGY"))

(in-package "ROS")
;;//! \htmlinclude simulation_strategy.msg.html


(defclass nubot_common::simulation_strategy
  :super ros::object
  :slots (_strategy_msgs ))

(defmethod nubot_common::simulation_strategy
  (:init
   (&key
    ((:strategy_msgs __strategy_msgs) (let (r) (dotimes (i 0) (push (instance nubot_common::StrategyInfo :init) r)) r))
    )
   (send-super :init)
   (setq _strategy_msgs __strategy_msgs)
   self)
  (:strategy_msgs
   (&rest __strategy_msgs)
   (if (keywordp (car __strategy_msgs))
       (send* _strategy_msgs __strategy_msgs)
     (progn
       (if __strategy_msgs (setq _strategy_msgs (car __strategy_msgs)))
       _strategy_msgs)))
  (:serialization-length
   ()
   (+
    ;; nubot_common/StrategyInfo[] _strategy_msgs
    (apply #'+ (send-all _strategy_msgs :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; nubot_common/StrategyInfo[] _strategy_msgs
     (write-long (length _strategy_msgs) s)
     (dolist (elem _strategy_msgs)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; nubot_common/StrategyInfo[] _strategy_msgs
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _strategy_msgs (let (r) (dotimes (i n) (push (instance nubot_common::StrategyInfo :init) r)) r))
     (dolist (elem- _strategy_msgs)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get nubot_common::simulation_strategy :md5sum-) "1d84999556ec502fdeaed67902dd635f")
(setf (get nubot_common::simulation_strategy :datatype-) "nubot_common/simulation_strategy")
(setf (get nubot_common::simulation_strategy :definition-)
      "StrategyInfo[] strategy_msgs

================================================================================
MSG: nubot_common/StrategyInfo
Header   header
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



(provide :nubot_common/simulation_strategy "1d84999556ec502fdeaed67902dd635f")


