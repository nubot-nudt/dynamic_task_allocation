; Auto-generated. Do not edit!


(cl:in-package nubot_common-msg)


;//! \htmlinclude RobotInfo.msg.html

(cl:defclass <RobotInfo> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (AgentID
    :reader AgentID
    :initarg :AgentID
    :type cl:integer
    :initform 0)
   (pos
    :reader pos
    :initarg :pos
    :type nubot_common-msg:Point2d
    :initform (cl:make-instance 'nubot_common-msg:Point2d))
   (heading
    :reader heading
    :initarg :heading
    :type nubot_common-msg:Angle
    :initform (cl:make-instance 'nubot_common-msg:Angle))
   (vrot
    :reader vrot
    :initarg :vrot
    :type cl:float
    :initform 0.0)
   (vtrans
    :reader vtrans
    :initarg :vtrans
    :type nubot_common-msg:Point2d
    :initform (cl:make-instance 'nubot_common-msg:Point2d))
   (iskick
    :reader iskick
    :initarg :iskick
    :type cl:boolean
    :initform cl:nil)
   (isvalid
    :reader isvalid
    :initarg :isvalid
    :type cl:boolean
    :initform cl:nil)
   (isstuck
    :reader isstuck
    :initarg :isstuck
    :type cl:boolean
    :initform cl:nil)
   (isdribble
    :reader isdribble
    :initarg :isdribble
    :type cl:boolean
    :initform cl:nil)
   (current_role
    :reader current_role
    :initarg :current_role
    :type cl:integer
    :initform 0)
   (role_time
    :reader role_time
    :initarg :role_time
    :type cl:float
    :initform 0.0)
   (target
    :reader target
    :initarg :target
    :type nubot_common-msg:Point2d
    :initform (cl:make-instance 'nubot_common-msg:Point2d)))
)

(cl:defclass RobotInfo (<RobotInfo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RobotInfo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RobotInfo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nubot_common-msg:<RobotInfo> is deprecated: use nubot_common-msg:RobotInfo instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <RobotInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:header-val is deprecated.  Use nubot_common-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'AgentID-val :lambda-list '(m))
(cl:defmethod AgentID-val ((m <RobotInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:AgentID-val is deprecated.  Use nubot_common-msg:AgentID instead.")
  (AgentID m))

(cl:ensure-generic-function 'pos-val :lambda-list '(m))
(cl:defmethod pos-val ((m <RobotInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:pos-val is deprecated.  Use nubot_common-msg:pos instead.")
  (pos m))

(cl:ensure-generic-function 'heading-val :lambda-list '(m))
(cl:defmethod heading-val ((m <RobotInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:heading-val is deprecated.  Use nubot_common-msg:heading instead.")
  (heading m))

(cl:ensure-generic-function 'vrot-val :lambda-list '(m))
(cl:defmethod vrot-val ((m <RobotInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:vrot-val is deprecated.  Use nubot_common-msg:vrot instead.")
  (vrot m))

(cl:ensure-generic-function 'vtrans-val :lambda-list '(m))
(cl:defmethod vtrans-val ((m <RobotInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:vtrans-val is deprecated.  Use nubot_common-msg:vtrans instead.")
  (vtrans m))

(cl:ensure-generic-function 'iskick-val :lambda-list '(m))
(cl:defmethod iskick-val ((m <RobotInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:iskick-val is deprecated.  Use nubot_common-msg:iskick instead.")
  (iskick m))

(cl:ensure-generic-function 'isvalid-val :lambda-list '(m))
(cl:defmethod isvalid-val ((m <RobotInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:isvalid-val is deprecated.  Use nubot_common-msg:isvalid instead.")
  (isvalid m))

(cl:ensure-generic-function 'isstuck-val :lambda-list '(m))
(cl:defmethod isstuck-val ((m <RobotInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:isstuck-val is deprecated.  Use nubot_common-msg:isstuck instead.")
  (isstuck m))

(cl:ensure-generic-function 'isdribble-val :lambda-list '(m))
(cl:defmethod isdribble-val ((m <RobotInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:isdribble-val is deprecated.  Use nubot_common-msg:isdribble instead.")
  (isdribble m))

(cl:ensure-generic-function 'current_role-val :lambda-list '(m))
(cl:defmethod current_role-val ((m <RobotInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:current_role-val is deprecated.  Use nubot_common-msg:current_role instead.")
  (current_role m))

(cl:ensure-generic-function 'role_time-val :lambda-list '(m))
(cl:defmethod role_time-val ((m <RobotInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:role_time-val is deprecated.  Use nubot_common-msg:role_time instead.")
  (role_time m))

(cl:ensure-generic-function 'target-val :lambda-list '(m))
(cl:defmethod target-val ((m <RobotInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:target-val is deprecated.  Use nubot_common-msg:target instead.")
  (target m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RobotInfo>) ostream)
  "Serializes a message object of type '<RobotInfo>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let* ((signed (cl:slot-value msg 'AgentID)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pos) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'heading) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vrot))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'vtrans) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'iskick) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'isvalid) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'isstuck) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'isdribble) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'current_role)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'role_time))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'target) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RobotInfo>) istream)
  "Deserializes a message object of type '<RobotInfo>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'AgentID) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pos) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'heading) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vrot) (roslisp-utils:decode-single-float-bits bits)))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'vtrans) istream)
    (cl:setf (cl:slot-value msg 'iskick) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'isvalid) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'isstuck) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'isdribble) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'current_role)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'role_time) (roslisp-utils:decode-single-float-bits bits)))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'target) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RobotInfo>)))
  "Returns string type for a message object of type '<RobotInfo>"
  "nubot_common/RobotInfo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RobotInfo)))
  "Returns string type for a message object of type 'RobotInfo"
  "nubot_common/RobotInfo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RobotInfo>)))
  "Returns md5sum for a message object of type '<RobotInfo>"
  "a028ed4c7ddb1dc95486b7c6059da8ad")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RobotInfo)))
  "Returns md5sum for a message object of type 'RobotInfo"
  "a028ed4c7ddb1dc95486b7c6059da8ad")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RobotInfo>)))
  "Returns full string definition for message of type '<RobotInfo>"
  (cl:format cl:nil "Header header~%int32    AgentID~%Point2d  pos~%Angle    heading~%float32  vrot~%Point2d  vtrans~%bool     iskick     ~%bool     isvalid ~%bool     isstuck ~%bool     isdribble~%char     current_role~%float32  role_time~%Point2d  target~% ~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nubot_common/Point2d~%float32 x~%float32 y~%~%================================================================================~%MSG: nubot_common/Angle~%float32 theta~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RobotInfo)))
  "Returns full string definition for message of type 'RobotInfo"
  (cl:format cl:nil "Header header~%int32    AgentID~%Point2d  pos~%Angle    heading~%float32  vrot~%Point2d  vtrans~%bool     iskick     ~%bool     isvalid ~%bool     isstuck ~%bool     isdribble~%char     current_role~%float32  role_time~%Point2d  target~% ~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nubot_common/Point2d~%float32 x~%float32 y~%~%================================================================================~%MSG: nubot_common/Angle~%float32 theta~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RobotInfo>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pos))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'heading))
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'vtrans))
     1
     1
     1
     1
     1
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'target))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RobotInfo>))
  "Converts a ROS message object to a list"
  (cl:list 'RobotInfo
    (cl:cons ':header (header msg))
    (cl:cons ':AgentID (AgentID msg))
    (cl:cons ':pos (pos msg))
    (cl:cons ':heading (heading msg))
    (cl:cons ':vrot (vrot msg))
    (cl:cons ':vtrans (vtrans msg))
    (cl:cons ':iskick (iskick msg))
    (cl:cons ':isvalid (isvalid msg))
    (cl:cons ':isstuck (isstuck msg))
    (cl:cons ':isdribble (isdribble msg))
    (cl:cons ':current_role (current_role msg))
    (cl:cons ':role_time (role_time msg))
    (cl:cons ':target (target msg))
))
