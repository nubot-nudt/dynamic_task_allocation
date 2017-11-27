; Auto-generated. Do not edit!


(cl:in-package nubot_common-msg)


;//! \htmlinclude PPoint.msg.html

(cl:defclass <PPoint> (roslisp-msg-protocol:ros-message)
  ((angle
    :reader angle
    :initarg :angle
    :type cl:float
    :initform 0.0)
   (radius
    :reader radius
    :initarg :radius
    :type cl:float
    :initform 0.0))
)

(cl:defclass PPoint (<PPoint>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PPoint>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PPoint)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name nubot_common-msg:<PPoint> is deprecated: use nubot_common-msg:PPoint instead.")))

(cl:ensure-generic-function 'angle-val :lambda-list '(m))
(cl:defmethod angle-val ((m <PPoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:angle-val is deprecated.  Use nubot_common-msg:angle instead.")
  (angle m))

(cl:ensure-generic-function 'radius-val :lambda-list '(m))
(cl:defmethod radius-val ((m <PPoint>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader nubot_common-msg:radius-val is deprecated.  Use nubot_common-msg:radius instead.")
  (radius m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PPoint>) ostream)
  "Serializes a message object of type '<PPoint>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'radius))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PPoint>) istream)
  "Deserializes a message object of type '<PPoint>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angle) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'radius) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PPoint>)))
  "Returns string type for a message object of type '<PPoint>"
  "nubot_common/PPoint")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PPoint)))
  "Returns string type for a message object of type 'PPoint"
  "nubot_common/PPoint")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PPoint>)))
  "Returns md5sum for a message object of type '<PPoint>"
  "29d7d0dfcbdb558f82b1c2caff948161")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PPoint)))
  "Returns md5sum for a message object of type 'PPoint"
  "29d7d0dfcbdb558f82b1c2caff948161")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PPoint>)))
  "Returns full string definition for message of type '<PPoint>"
  (cl:format cl:nil "float32 angle~%float32 radius~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PPoint)))
  "Returns full string definition for message of type 'PPoint"
  (cl:format cl:nil "float32 angle~%float32 radius~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PPoint>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PPoint>))
  "Converts a ROS message object to a list"
  (cl:list 'PPoint
    (cl:cons ':angle (angle msg))
    (cl:cons ':radius (radius msg))
))
