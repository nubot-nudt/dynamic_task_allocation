;; Auto-generated. Do not edit!


(when (boundp 'nubot_common::BallInfo3d)
  (if (not (find-package "NUBOT_COMMON"))
    (make-package "NUBOT_COMMON"))
  (shadow 'BallInfo3d (find-package "NUBOT_COMMON")))
(unless (find-package "NUBOT_COMMON::BALLINFO3D")
  (make-package "NUBOT_COMMON::BALLINFO3D"))

(in-package "ROS")
;;//! \htmlinclude BallInfo3d.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass nubot_common::BallInfo3d
  :super ros::object
  :slots (_header _pos _velocity _pos_known_3d _pos_known_2d _velocity_known ))

(defmethod nubot_common::BallInfo3d
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:pos __pos) (instance nubot_common::Point3d :init))
    ((:velocity __velocity) (instance nubot_common::Point3d :init))
    ((:pos_known_3d __pos_known_3d) nil)
    ((:pos_known_2d __pos_known_2d) nil)
    ((:velocity_known __velocity_known) nil)
    )
   (send-super :init)
   (setq _header __header)
   (setq _pos __pos)
   (setq _velocity __velocity)
   (setq _pos_known_3d __pos_known_3d)
   (setq _pos_known_2d __pos_known_2d)
   (setq _velocity_known __velocity_known)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:pos
   (&rest __pos)
   (if (keywordp (car __pos))
       (send* _pos __pos)
     (progn
       (if __pos (setq _pos (car __pos)))
       _pos)))
  (:velocity
   (&rest __velocity)
   (if (keywordp (car __velocity))
       (send* _velocity __velocity)
     (progn
       (if __velocity (setq _velocity (car __velocity)))
       _velocity)))
  (:pos_known_3d
   (&optional __pos_known_3d)
   (if __pos_known_3d (setq _pos_known_3d __pos_known_3d)) _pos_known_3d)
  (:pos_known_2d
   (&optional __pos_known_2d)
   (if __pos_known_2d (setq _pos_known_2d __pos_known_2d)) _pos_known_2d)
  (:velocity_known
   (&optional __velocity_known)
   (if __velocity_known (setq _velocity_known __velocity_known)) _velocity_known)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; nubot_common/Point3d _pos
    (send _pos :serialization-length)
    ;; nubot_common/Point3d _velocity
    (send _velocity :serialization-length)
    ;; bool _pos_known_3d
    1
    ;; bool _pos_known_2d
    1
    ;; bool _velocity_known
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; nubot_common/Point3d _pos
       (send _pos :serialize s)
     ;; nubot_common/Point3d _velocity
       (send _velocity :serialize s)
     ;; bool _pos_known_3d
       (if _pos_known_3d (write-byte -1 s) (write-byte 0 s))
     ;; bool _pos_known_2d
       (if _pos_known_2d (write-byte -1 s) (write-byte 0 s))
     ;; bool _velocity_known
       (if _velocity_known (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; nubot_common/Point3d _pos
     (send _pos :deserialize buf ptr-) (incf ptr- (send _pos :serialization-length))
   ;; nubot_common/Point3d _velocity
     (send _velocity :deserialize buf ptr-) (incf ptr- (send _velocity :serialization-length))
   ;; bool _pos_known_3d
     (setq _pos_known_3d (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _pos_known_2d
     (setq _pos_known_2d (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _velocity_known
     (setq _velocity_known (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get nubot_common::BallInfo3d :md5sum-) "6634a529c2fba000f06cf99f5ab31312")
(setf (get nubot_common::BallInfo3d :datatype-) "nubot_common/BallInfo3d")
(setf (get nubot_common::BallInfo3d :definition-)
      "Header header
Point3d   pos
Point3d   velocity
bool      pos_known_3d
bool      pos_known_2d
bool      velocity_known

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
MSG: nubot_common/Point3d
float32 x
float32 y
float32 z

")



(provide :nubot_common/BallInfo3d "6634a529c2fba000f06cf99f5ab31312")


