; Auto-generated. Do not edit!


(cl:in-package nubot_common-msg)


;//! \htmlinclude WorldModelInfo.msg.html

(cl:defclass <WorldModelInfo> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (obstacleinfo
    :reader obstacleinfo
    :initarg :obstacleinfo
    :type nubot_common-msg:ObstaclesInfo
    :initform (cl:make-instance 'nubot_common-msg:ObstaclesInfo))
   (oppinfo
    :reader oppinfo
    :initarg :oppinfo
    :type nubot_common-msg:ObstaclesInfo
    :initform (cl:make-instance 'nubot_common-msg:ObstaclesInfo))
   (robotinfo
    :reader robotinfo
    :initarg :robotinfo
    :type (cl:vector nubot_common-msg:RobotInfo)
   :initform (cl:make-array 0 :element-type 'nubot_common-msg:RobotInfo :initial-element (cl:make-instance 'nubot_common-msg:RobotInfo)))
   (ballinfo
    :reader ballinfo
    :initarg :ballinfo
    :type (cl:vector nubot_common-msg:BallInfo)
   :initform (cl:make-array 0 :element-type 'nubot_common-msg:BallInfo :initial-element (cl:make-instance 'nubot_common-msg:BallInfo)))
   (coachinfo
    :reader coachinfo
    :initarg :coachinfo
    :type nubot_common-msg:CoachInfo
    :initform (cl:make-instance 'nubot_common-msg:CoachInfo)))
)

(cl:defclass WorldModelInfo (<WorldModelInfo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <WorldModelInfo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'WorldModelInfo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nubot_common-msg:<WorldModelInfo> is deprecated: use nubot_common-msg:WorldModelInfo instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <WorldModelInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:header-val is deprecated.  Use nubot_common-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'obstacleinfo-val :lambda-list '(m))
(cl:defmethod obstacleinfo-val ((m <WorldModelInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:obstacleinfo-val is deprecated.  Use nubot_common-msg:obstacleinfo instead.")
  (obstacleinfo m))

(cl:ensure-generic-function 'oppinfo-val :lambda-list '(m))
(cl:defmethod oppinfo-val ((m <WorldModelInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:oppinfo-val is deprecated.  Use nubot_common-msg:oppinfo instead.")
  (oppinfo m))

(cl:ensure-generic-function 'robotinfo-val :lambda-list '(m))
(cl:defmethod robotinfo-val ((m <WorldModelInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:robotinfo-val is deprecated.  Use nubot_common-msg:robotinfo instead.")
  (robotinfo m))

(cl:ensure-generic-function 'ballinfo-val :lambda-list '(m))
(cl:defmethod ballinfo-val ((m <WorldModelInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:ballinfo-val is deprecated.  Use nubot_common-msg:ballinfo instead.")
  (ballinfo m))

(cl:ensure-generic-function 'coachinfo-val :lambda-list '(m))
(cl:defmethod coachinfo-val ((m <WorldModelInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:coachinfo-val is deprecated.  Use nubot_common-msg:coachinfo instead.")
  (coachinfo m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <WorldModelInfo>) ostream)
  "Serializes a message object of type '<WorldModelInfo>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'obstacleinfo) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'oppinfo) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'robotinfo))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'robotinfo))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'ballinfo))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'ballinfo))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'coachinfo) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <WorldModelInfo>) istream)
  "Deserializes a message object of type '<WorldModelInfo>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'obstacleinfo) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'oppinfo) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'robotinfo) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'robotinfo)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'nubot_common-msg:RobotInfo))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'ballinfo) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'ballinfo)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'nubot_common-msg:BallInfo))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'coachinfo) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<WorldModelInfo>)))
  "Returns string type for a message object of type '<WorldModelInfo>"
  "nubot_common/WorldModelInfo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'WorldModelInfo)))
  "Returns string type for a message object of type 'WorldModelInfo"
  "nubot_common/WorldModelInfo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<WorldModelInfo>)))
  "Returns md5sum for a message object of type '<WorldModelInfo>"
  "e902738e8fde937e2be378951669848c")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'WorldModelInfo)))
  "Returns md5sum for a message object of type 'WorldModelInfo"
  "e902738e8fde937e2be378951669848c")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<WorldModelInfo>)))
  "Returns full string definition for message of type '<WorldModelInfo>"
  (cl:format cl:nil "Header header~%ObstaclesInfo obstacleinfo~%ObstaclesInfo oppinfo~%RobotInfo[]   robotinfo~%BallInfo[]    ballinfo~%CoachInfo     coachinfo~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nubot_common/ObstaclesInfo~%Header header~%Point2d[] pos~%PPoint[] polar_pos~%~%~%================================================================================~%MSG: nubot_common/Point2d~%float32 x~%float32 y~%~%================================================================================~%MSG: nubot_common/PPoint~%float32 angle~%float32 radius~%~%================================================================================~%MSG: nubot_common/RobotInfo~%Header header~%int32    AgentID~%Point2d  pos~%Angle    heading~%float32  vrot~%Point2d  vtrans~%bool     iskick     ~%bool     isvalid ~%bool     isstuck ~%bool     isdribble~%char     current_role~%float32  role_time~%Point2d  target~% ~%~%================================================================================~%MSG: nubot_common/Angle~%float32 theta~%~%================================================================================~%MSG: nubot_common/BallInfo~%Header header~%int32     ballinfostate~%Point2d   pos~%PPoint    real_pos~%Point2d   velocity~%bool      pos_known~%bool      velocity_known~%~%~%================================================================================~%MSG: nubot_common/CoachInfo~%Header header~%char MatchMode~%char MatchType~%char TestMode           ~%Point2d pointA~%Point2d pointB~%int16 angleA~%int16 angleB~%char idA~%char idB~%char kickforce~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'WorldModelInfo)))
  "Returns full string definition for message of type 'WorldModelInfo"
  (cl:format cl:nil "Header header~%ObstaclesInfo obstacleinfo~%ObstaclesInfo oppinfo~%RobotInfo[]   robotinfo~%BallInfo[]    ballinfo~%CoachInfo     coachinfo~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nubot_common/ObstaclesInfo~%Header header~%Point2d[] pos~%PPoint[] polar_pos~%~%~%================================================================================~%MSG: nubot_common/Point2d~%float32 x~%float32 y~%~%================================================================================~%MSG: nubot_common/PPoint~%float32 angle~%float32 radius~%~%================================================================================~%MSG: nubot_common/RobotInfo~%Header header~%int32    AgentID~%Point2d  pos~%Angle    heading~%float32  vrot~%Point2d  vtrans~%bool     iskick     ~%bool     isvalid ~%bool     isstuck ~%bool     isdribble~%char     current_role~%float32  role_time~%Point2d  target~% ~%~%================================================================================~%MSG: nubot_common/Angle~%float32 theta~%~%================================================================================~%MSG: nubot_common/BallInfo~%Header header~%int32     ballinfostate~%Point2d   pos~%PPoint    real_pos~%Point2d   velocity~%bool      pos_known~%bool      velocity_known~%~%~%================================================================================~%MSG: nubot_common/CoachInfo~%Header header~%char MatchMode~%char MatchType~%char TestMode           ~%Point2d pointA~%Point2d pointB~%int16 angleA~%int16 angleB~%char idA~%char idB~%char kickforce~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <WorldModelInfo>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'obstacleinfo))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'oppinfo))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'robotinfo) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'ballinfo) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'coachinfo))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <WorldModelInfo>))
  "Converts a ROS message object to a list"
  (cl:list 'WorldModelInfo
    (cl:cons ':header (header msg))
    (cl:cons ':obstacleinfo (obstacleinfo msg))
    (cl:cons ':oppinfo (oppinfo msg))
    (cl:cons ':robotinfo (robotinfo msg))
    (cl:cons ':ballinfo (ballinfo msg))
    (cl:cons ':coachinfo (coachinfo msg))
))
