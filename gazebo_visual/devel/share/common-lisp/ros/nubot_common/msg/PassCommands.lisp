; Auto-generated. Do not edit!


(cl:in-package nubot_common-msg)


;//! \htmlinclude PassCommands.msg.html

(cl:defclass <PassCommands> (roslisp-msg-protocol:ros-message)
  ((pass_id
    :reader pass_id
    :initarg :pass_id
    :type cl:integer
    :initform 0)
   (catch_id
    :reader catch_id
    :initarg :catch_id
    :type cl:integer
    :initform 0)
   (pass_pt
    :reader pass_pt
    :initarg :pass_pt
    :type nubot_common-msg:Point2d
    :initform (cl:make-instance 'nubot_common-msg:Point2d))
   (catch_pt
    :reader catch_pt
    :initarg :catch_pt
    :type nubot_common-msg:Point2d
    :initform (cl:make-instance 'nubot_common-msg:Point2d))
   (is_passout
    :reader is_passout
    :initarg :is_passout
    :type cl:boolean
    :initform cl:nil)
   (is_dynamic_pass
    :reader is_dynamic_pass
    :initarg :is_dynamic_pass
    :type cl:boolean
    :initform cl:nil)
   (is_static_pass
    :reader is_static_pass
    :initarg :is_static_pass
    :type cl:boolean
    :initform cl:nil)
   (is_valid
    :reader is_valid
    :initarg :is_valid
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass PassCommands (<PassCommands>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PassCommands>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PassCommands)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nubot_common-msg:<PassCommands> is deprecated: use nubot_common-msg:PassCommands instead.")))

(cl:ensure-generic-function 'pass_id-val :lambda-list '(m))
(cl:defmethod pass_id-val ((m <PassCommands>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:pass_id-val is deprecated.  Use nubot_common-msg:pass_id instead.")
  (pass_id m))

(cl:ensure-generic-function 'catch_id-val :lambda-list '(m))
(cl:defmethod catch_id-val ((m <PassCommands>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:catch_id-val is deprecated.  Use nubot_common-msg:catch_id instead.")
  (catch_id m))

(cl:ensure-generic-function 'pass_pt-val :lambda-list '(m))
(cl:defmethod pass_pt-val ((m <PassCommands>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:pass_pt-val is deprecated.  Use nubot_common-msg:pass_pt instead.")
  (pass_pt m))

(cl:ensure-generic-function 'catch_pt-val :lambda-list '(m))
(cl:defmethod catch_pt-val ((m <PassCommands>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:catch_pt-val is deprecated.  Use nubot_common-msg:catch_pt instead.")
  (catch_pt m))

(cl:ensure-generic-function 'is_passout-val :lambda-list '(m))
(cl:defmethod is_passout-val ((m <PassCommands>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:is_passout-val is deprecated.  Use nubot_common-msg:is_passout instead.")
  (is_passout m))

(cl:ensure-generic-function 'is_dynamic_pass-val :lambda-list '(m))
(cl:defmethod is_dynamic_pass-val ((m <PassCommands>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:is_dynamic_pass-val is deprecated.  Use nubot_common-msg:is_dynamic_pass instead.")
  (is_dynamic_pass m))

(cl:ensure-generic-function 'is_static_pass-val :lambda-list '(m))
(cl:defmethod is_static_pass-val ((m <PassCommands>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:is_static_pass-val is deprecated.  Use nubot_common-msg:is_static_pass instead.")
  (is_static_pass m))

(cl:ensure-generic-function 'is_valid-val :lambda-list '(m))
(cl:defmethod is_valid-val ((m <PassCommands>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:is_valid-val is deprecated.  Use nubot_common-msg:is_valid instead.")
  (is_valid m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PassCommands>) ostream)
  "Serializes a message object of type '<PassCommands>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'pass_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'pass_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'pass_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'pass_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'catch_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'catch_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'catch_id)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'catch_id)) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pass_pt) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'catch_pt) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'is_passout) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'is_dynamic_pass) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'is_static_pass) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'is_valid) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PassCommands>) istream)
  "Deserializes a message object of type '<PassCommands>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'pass_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'pass_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'pass_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'pass_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'catch_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'catch_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) (cl:slot-value msg 'catch_id)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) (cl:slot-value msg 'catch_id)) (cl:read-byte istream))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pass_pt) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'catch_pt) istream)
    (cl:setf (cl:slot-value msg 'is_passout) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'is_dynamic_pass) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'is_static_pass) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'is_valid) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PassCommands>)))
  "Returns string type for a message object of type '<PassCommands>"
  "nubot_common/PassCommands")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PassCommands)))
  "Returns string type for a message object of type 'PassCommands"
  "nubot_common/PassCommands")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PassCommands>)))
  "Returns md5sum for a message object of type '<PassCommands>"
  "d50d66ad0a96e8d9eae8a7a9da579ad2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PassCommands)))
  "Returns md5sum for a message object of type 'PassCommands"
  "d50d66ad0a96e8d9eae8a7a9da579ad2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PassCommands>)))
  "Returns full string definition for message of type '<PassCommands>"
  (cl:format cl:nil "uint32  pass_id~%uint32  catch_id~%Point2d pass_pt~%Point2d catch_pt~%bool    is_passout~%bool    is_dynamic_pass~%bool    is_static_pass~%bool    is_valid~% ~%~%================================================================================~%MSG: nubot_common/Point2d~%float32 x~%float32 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PassCommands)))
  "Returns full string definition for message of type 'PassCommands"
  (cl:format cl:nil "uint32  pass_id~%uint32  catch_id~%Point2d pass_pt~%Point2d catch_pt~%bool    is_passout~%bool    is_dynamic_pass~%bool    is_static_pass~%bool    is_valid~% ~%~%================================================================================~%MSG: nubot_common/Point2d~%float32 x~%float32 y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PassCommands>))
  (cl:+ 0
     4
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pass_pt))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'catch_pt))
     1
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PassCommands>))
  "Converts a ROS message object to a list"
  (cl:list 'PassCommands
    (cl:cons ':pass_id (pass_id msg))
    (cl:cons ':catch_id (catch_id msg))
    (cl:cons ':pass_pt (pass_pt msg))
    (cl:cons ':catch_pt (catch_pt msg))
    (cl:cons ':is_passout (is_passout msg))
    (cl:cons ':is_dynamic_pass (is_dynamic_pass msg))
    (cl:cons ':is_static_pass (is_static_pass msg))
    (cl:cons ':is_valid (is_valid msg))
))
