; Auto-generated. Do not edit!


(cl:in-package nubot_common-msg)


;//! \htmlinclude simulation_strategy.msg.html

(cl:defclass <simulation_strategy> (roslisp-msg-protocol:ros-message)
  ((strategy_msgs
    :reader strategy_msgs
    :initarg :strategy_msgs
    :type (cl:vector nubot_common-msg:StrategyInfo)
   :initform (cl:make-array 0 :element-type 'nubot_common-msg:StrategyInfo :initial-element (cl:make-instance 'nubot_common-msg:StrategyInfo))))
)

(cl:defclass simulation_strategy (<simulation_strategy>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <simulation_strategy>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'simulation_strategy)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nubot_common-msg:<simulation_strategy> is deprecated: use nubot_common-msg:simulation_strategy instead.")))

(cl:ensure-generic-function 'strategy_msgs-val :lambda-list '(m))
(cl:defmethod strategy_msgs-val ((m <simulation_strategy>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:strategy_msgs-val is deprecated.  Use nubot_common-msg:strategy_msgs instead.")
  (strategy_msgs m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <simulation_strategy>) ostream)
  "Serializes a message object of type '<simulation_strategy>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'strategy_msgs))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'strategy_msgs))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <simulation_strategy>) istream)
  "Deserializes a message object of type '<simulation_strategy>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'strategy_msgs) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'strategy_msgs)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'nubot_common-msg:StrategyInfo))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<simulation_strategy>)))
  "Returns string type for a message object of type '<simulation_strategy>"
  "nubot_common/simulation_strategy")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'simulation_strategy)))
  "Returns string type for a message object of type 'simulation_strategy"
  "nubot_common/simulation_strategy")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<simulation_strategy>)))
  "Returns md5sum for a message object of type '<simulation_strategy>"
  "1d84999556ec502fdeaed67902dd635f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'simulation_strategy)))
  "Returns md5sum for a message object of type 'simulation_strategy"
  "1d84999556ec502fdeaed67902dd635f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<simulation_strategy>)))
  "Returns full string definition for message of type '<simulation_strategy>"
  (cl:format cl:nil "StrategyInfo[] strategy_msgs~%~%================================================================================~%MSG: nubot_common/StrategyInfo~%Header   header~%int32    AgentID~%int32    targetNum1~%int32    targetNum2~%int32    targetNum3~%int32    targetNum4~%int32    staticpassNum~%int32    staticcatchNum~%uint32   role~%uint32   action~%bool     is_dribble~%bool     is_kickoff~%float32  role_time~%PassCommands  pass_cmd~%~%~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nubot_common/PassCommands~%uint32  pass_id~%uint32  catch_id~%Point2d pass_pt~%Point2d catch_pt~%bool    is_passout~%bool    is_dynamic_pass~%bool    is_static_pass~%bool    is_valid~% ~%~%================================================================================~%MSG: nubot_common/Point2d~%float32 x~%float32 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'simulation_strategy)))
  "Returns full string definition for message of type 'simulation_strategy"
  (cl:format cl:nil "StrategyInfo[] strategy_msgs~%~%================================================================================~%MSG: nubot_common/StrategyInfo~%Header   header~%int32    AgentID~%int32    targetNum1~%int32    targetNum2~%int32    targetNum3~%int32    targetNum4~%int32    staticpassNum~%int32    staticcatchNum~%uint32   role~%uint32   action~%bool     is_dribble~%bool     is_kickoff~%float32  role_time~%PassCommands  pass_cmd~%~%~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nubot_common/PassCommands~%uint32  pass_id~%uint32  catch_id~%Point2d pass_pt~%Point2d catch_pt~%bool    is_passout~%bool    is_dynamic_pass~%bool    is_static_pass~%bool    is_valid~% ~%~%================================================================================~%MSG: nubot_common/Point2d~%float32 x~%float32 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <simulation_strategy>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'strategy_msgs) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <simulation_strategy>))
  "Converts a ROS message object to a list"
  (cl:list 'simulation_strategy
    (cl:cons ':strategy_msgs (strategy_msgs msg))
))
