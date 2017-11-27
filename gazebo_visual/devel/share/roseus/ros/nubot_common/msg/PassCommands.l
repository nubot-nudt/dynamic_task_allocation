;; Auto-generated. Do not edit!


(when (boundp 'nubot_common::PassCommands)
  (if (not (find-package "NUBOT_COMMON"))
    (make-package "NUBOT_COMMON"))
  (shadow 'PassCommands (find-package "NUBOT_COMMON")))
(unless (find-package "NUBOT_COMMON::PASSCOMMANDS")
  (make-package "NUBOT_COMMON::PASSCOMMANDS"))

(in-package "ROS")
;;//! \htmlinclude PassCommands.msg.html


(defclass nubot_common::PassCommands
  :super ros::object
  :slots (_pass_id _catch_id _pass_pt _catch_pt _is_passout _is_dynamic_pass _is_static_pass _is_valid ))

(defmethod nubot_common::PassCommands
  (:init
   (&key
    ((:pass_id __pass_id) 0)
    ((:catch_id __catch_id) 0)
    ((:pass_pt __pass_pt) (instance nubot_common::Point2d :init))
    ((:catch_pt __catch_pt) (instance nubot_common::Point2d :init))
    ((:is_passout __is_passout) nil)
    ((:is_dynamic_pass __is_dynamic_pass) nil)
    ((:is_static_pass __is_static_pass) nil)
    ((:is_valid __is_valid) nil)
    )
   (send-super :init)
   (setq _pass_id (round __pass_id))
   (setq _catch_id (round __catch_id))
   (setq _pass_pt __pass_pt)
   (setq _catch_pt __catch_pt)
   (setq _is_passout __is_passout)
   (setq _is_dynamic_pass __is_dynamic_pass)
   (setq _is_static_pass __is_static_pass)
   (setq _is_valid __is_valid)
   self)
  (:pass_id
   (&optional __pass_id)
   (if __pass_id (setq _pass_id __pass_id)) _pass_id)
  (:catch_id
   (&optional __catch_id)
   (if __catch_id (setq _catch_id __catch_id)) _catch_id)
  (:pass_pt
   (&rest __pass_pt)
   (if (keywordp (car __pass_pt))
       (send* _pass_pt __pass_pt)
     (progn
       (if __pass_pt (setq _pass_pt (car __pass_pt)))
       _pass_pt)))
  (:catch_pt
   (&rest __catch_pt)
   (if (keywordp (car __catch_pt))
       (send* _catch_pt __catch_pt)
     (progn
       (if __catch_pt (setq _catch_pt (car __catch_pt)))
       _catch_pt)))
  (:is_passout
   (&optional __is_passout)
   (if __is_passout (setq _is_passout __is_passout)) _is_passout)
  (:is_dynamic_pass
   (&optional __is_dynamic_pass)
   (if __is_dynamic_pass (setq _is_dynamic_pass __is_dynamic_pass)) _is_dynamic_pass)
  (:is_static_pass
   (&optional __is_static_pass)
   (if __is_static_pass (setq _is_static_pass __is_static_pass)) _is_static_pass)
  (:is_valid
   (&optional __is_valid)
   (if __is_valid (setq _is_valid __is_valid)) _is_valid)
  (:serialization-length
   ()
   (+
    ;; uint32 _pass_id
    4
    ;; uint32 _catch_id
    4
    ;; nubot_common/Point2d _pass_pt
    (send _pass_pt :serialization-length)
    ;; nubot_common/Point2d _catch_pt
    (send _catch_pt :serialization-length)
    ;; bool _is_passout
    1
    ;; bool _is_dynamic_pass
    1
    ;; bool _is_static_pass
    1
    ;; bool _is_valid
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint32 _pass_id
       (write-long _pass_id s)
     ;; uint32 _catch_id
       (write-long _catch_id s)
     ;; nubot_common/Point2d _pass_pt
       (send _pass_pt :serialize s)
     ;; nubot_common/Point2d _catch_pt
       (send _catch_pt :serialize s)
     ;; bool _is_passout
       (if _is_passout (write-byte -1 s) (write-byte 0 s))
     ;; bool _is_dynamic_pass
       (if _is_dynamic_pass (write-byte -1 s) (write-byte 0 s))
     ;; bool _is_static_pass
       (if _is_static_pass (write-byte -1 s) (write-byte 0 s))
     ;; bool _is_valid
       (if _is_valid (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint32 _pass_id
     (setq _pass_id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint32 _catch_id
     (setq _catch_id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; nubot_common/Point2d _pass_pt
     (send _pass_pt :deserialize buf ptr-) (incf ptr- (send _pass_pt :serialization-length))
   ;; nubot_common/Point2d _catch_pt
     (send _catch_pt :deserialize buf ptr-) (incf ptr- (send _catch_pt :serialization-length))
   ;; bool _is_passout
     (setq _is_passout (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _is_dynamic_pass
     (setq _is_dynamic_pass (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _is_static_pass
     (setq _is_static_pass (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _is_valid
     (setq _is_valid (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get nubot_common::PassCommands :md5sum-) "d50d66ad0a96e8d9eae8a7a9da579ad2")
(setf (get nubot_common::PassCommands :datatype-) "nubot_common/PassCommands")
(setf (get nubot_common::PassCommands :definition-)
      "uint32  pass_id
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



(provide :nubot_common/PassCommands "d50d66ad0a96e8d9eae8a7a9da579ad2")


