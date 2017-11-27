; Auto-generated. Do not edit!


(cl:in-package nubot_common-msg)


;//! \htmlinclude CoachInfo.msg.html

(cl:defclass <CoachInfo> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (MatchMode
    :reader MatchMode
    :initarg :MatchMode
    :type cl:integer
    :initform 0)
   (MatchType
    :reader MatchType
    :initarg :MatchType
    :type cl:integer
    :initform 0)
   (TestMode
    :reader TestMode
    :initarg :TestMode
    :type cl:integer
    :initform 0)
   (pointA
    :reader pointA
    :initarg :pointA
    :type nubot_common-msg:Point2d
    :initform (cl:make-instance 'nubot_common-msg:Point2d))
   (pointB
    :reader pointB
    :initarg :pointB
    :type nubot_common-msg:Point2d
    :initform (cl:make-instance 'nubot_common-msg:Point2d))
   (angleA
    :reader angleA
    :initarg :angleA
    :type cl:fixnum
    :initform 0)
   (angleB
    :reader angleB
    :initarg :angleB
    :type cl:fixnum
    :initform 0)
   (idA
    :reader idA
    :initarg :idA
    :type cl:integer
    :initform 0)
   (idB
    :reader idB
    :initarg :idB
    :type cl:integer
    :initform 0)
   (kickforce
    :reader kickforce
    :initarg :kickforce
    :type cl:integer
    :initform 0))
)

(cl:defclass CoachInfo (<CoachInfo>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CoachInfo>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CoachInfo)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nubot_common-msg:<CoachInfo> is deprecated: use nubot_common-msg:CoachInfo instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <CoachInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:header-val is deprecated.  Use nubot_common-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'MatchMode-val :lambda-list '(m))
(cl:defmethod MatchMode-val ((m <CoachInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:MatchMode-val is deprecated.  Use nubot_common-msg:MatchMode instead.")
  (MatchMode m))

(cl:ensure-generic-function 'MatchType-val :lambda-list '(m))
(cl:defmethod MatchType-val ((m <CoachInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:MatchType-val is deprecated.  Use nubot_common-msg:MatchType instead.")
  (MatchType m))

(cl:ensure-generic-function 'TestMode-val :lambda-list '(m))
(cl:defmethod TestMode-val ((m <CoachInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:TestMode-val is deprecated.  Use nubot_common-msg:TestMode instead.")
  (TestMode m))

(cl:ensure-generic-function 'pointA-val :lambda-list '(m))
(cl:defmethod pointA-val ((m <CoachInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:pointA-val is deprecated.  Use nubot_common-msg:pointA instead.")
  (pointA m))

(cl:ensure-generic-function 'pointB-val :lambda-list '(m))
(cl:defmethod pointB-val ((m <CoachInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:pointB-val is deprecated.  Use nubot_common-msg:pointB instead.")
  (pointB m))

(cl:ensure-generic-function 'angleA-val :lambda-list '(m))
(cl:defmethod angleA-val ((m <CoachInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:angleA-val is deprecated.  Use nubot_common-msg:angleA instead.")
  (angleA m))

(cl:ensure-generic-function 'angleB-val :lambda-list '(m))
(cl:defmethod angleB-val ((m <CoachInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:angleB-val is deprecated.  Use nubot_common-msg:angleB instead.")
  (angleB m))

(cl:ensure-generic-function 'idA-val :lambda-list '(m))
(cl:defmethod idA-val ((m <CoachInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:idA-val is deprecated.  Use nubot_common-msg:idA instead.")
  (idA m))

(cl:ensure-generic-function 'idB-val :lambda-list '(m))
(cl:defmethod idB-val ((m <CoachInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:idB-val is deprecated.  Use nubot_common-msg:idB instead.")
  (idB m))

(cl:ensure-generic-function 'kickforce-val :lambda-list '(m))
(cl:defmethod kickforce-val ((m <CoachInfo>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:kickforce-val is deprecated.  Use nubot_common-msg:kickforce instead.")
  (kickforce m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CoachInfo>) ostream)
  "Serializes a message object of type '<CoachInfo>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'MatchMode)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'MatchType)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'TestMode)) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pointA) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pointB) ostream)
  (cl:let* ((signed (cl:slot-value msg 'angleA)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'angleB)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'idA)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'idB)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'kickforce)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CoachInfo>) istream)
  "Deserializes a message object of type '<CoachInfo>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'MatchMode)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'MatchType)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'TestMode)) (cl:read-byte istream))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pointA) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pointB) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'angleA) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'angleB) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'idA)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'idB)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'kickforce)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CoachInfo>)))
  "Returns string type for a message object of type '<CoachInfo>"
  "nubot_common/CoachInfo")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CoachInfo)))
  "Returns string type for a message object of type 'CoachInfo"
  "nubot_common/CoachInfo")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CoachInfo>)))
  "Returns md5sum for a message object of type '<CoachInfo>"
  "7bb01a0f4328cb28beb61d4f502c2969")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CoachInfo)))
  "Returns md5sum for a message object of type 'CoachInfo"
  "7bb01a0f4328cb28beb61d4f502c2969")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CoachInfo>)))
  "Returns full string definition for message of type '<CoachInfo>"
  (cl:format cl:nil "Header header~%char MatchMode~%char MatchType~%char TestMode           ~%Point2d pointA~%Point2d pointB~%int16 angleA~%int16 angleB~%char idA~%char idB~%char kickforce~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nubot_common/Point2d~%float32 x~%float32 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CoachInfo)))
  "Returns full string definition for message of type 'CoachInfo"
  (cl:format cl:nil "Header header~%char MatchMode~%char MatchType~%char TestMode           ~%Point2d pointA~%Point2d pointB~%int16 angleA~%int16 angleB~%char idA~%char idB~%char kickforce~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: nubot_common/Point2d~%float32 x~%float32 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CoachInfo>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     1
     1
     1
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pointA))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pointB))
     2
     2
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CoachInfo>))
  "Converts a ROS message object to a list"
  (cl:list 'CoachInfo
    (cl:cons ':header (header msg))
    (cl:cons ':MatchMode (MatchMode msg))
    (cl:cons ':MatchType (MatchType msg))
    (cl:cons ':TestMode (TestMode msg))
    (cl:cons ':pointA (pointA msg))
    (cl:cons ':pointB (pointB msg))
    (cl:cons ':angleA (angleA msg))
    (cl:cons ':angleB (angleB msg))
    (cl:cons ':idA (idA msg))
    (cl:cons ':idB (idB msg))
    (cl:cons ':kickforce (kickforce msg))
))
