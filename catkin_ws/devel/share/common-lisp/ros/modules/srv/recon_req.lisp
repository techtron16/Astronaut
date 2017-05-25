; Auto-generated. Do not edit!


(cl:in-package modules-srv)


;//! \htmlinclude recon_req-request.msg.html

(cl:defclass <recon_req-request> (roslisp-msg-protocol:ros-message)
  ((tags
    :reader tags
    :initarg :tags
    :type (cl:vector std_msgs-msg:String)
   :initform (cl:make-array 0 :element-type 'std_msgs-msg:String :initial-element (cl:make-instance 'std_msgs-msg:String))))
)

(cl:defclass recon_req-request (<recon_req-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <recon_req-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'recon_req-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name modules-srv:<recon_req-request> is deprecated: use modules-srv:recon_req-request instead.")))

(cl:ensure-generic-function 'tags-val :lambda-list '(m))
(cl:defmethod tags-val ((m <recon_req-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader modules-srv:tags-val is deprecated.  Use modules-srv:tags instead.")
  (tags m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <recon_req-request>) ostream)
  "Serializes a message object of type '<recon_req-request>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'tags))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'tags))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <recon_req-request>) istream)
  "Deserializes a message object of type '<recon_req-request>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'tags) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'tags)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'std_msgs-msg:String))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<recon_req-request>)))
  "Returns string type for a service object of type '<recon_req-request>"
  "modules/recon_reqRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'recon_req-request)))
  "Returns string type for a service object of type 'recon_req-request"
  "modules/recon_reqRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<recon_req-request>)))
  "Returns md5sum for a message object of type '<recon_req-request>"
  "504293a32ca80b6b20fe52b4cc8a6439")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'recon_req-request)))
  "Returns md5sum for a message object of type 'recon_req-request"
  "504293a32ca80b6b20fe52b4cc8a6439")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<recon_req-request>)))
  "Returns full string definition for message of type '<recon_req-request>"
  (cl:format cl:nil "std_msgs/String[] tags~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'recon_req-request)))
  "Returns full string definition for message of type 'recon_req-request"
  (cl:format cl:nil "std_msgs/String[] tags~%~%================================================================================~%MSG: std_msgs/String~%string data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <recon_req-request>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'tags) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <recon_req-request>))
  "Converts a ROS message object to a list"
  (cl:list 'recon_req-request
    (cl:cons ':tags (tags msg))
))
;//! \htmlinclude recon_req-response.msg.html

(cl:defclass <recon_req-response> (roslisp-msg-protocol:ros-message)
  ((path
    :reader path
    :initarg :path
    :type nav_msgs-msg:Path
    :initform (cl:make-instance 'nav_msgs-msg:Path)))
)

(cl:defclass recon_req-response (<recon_req-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <recon_req-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'recon_req-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name modules-srv:<recon_req-response> is deprecated: use modules-srv:recon_req-response instead.")))

(cl:ensure-generic-function 'path-val :lambda-list '(m))
(cl:defmethod path-val ((m <recon_req-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader modules-srv:path-val is deprecated.  Use modules-srv:path instead.")
  (path m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <recon_req-response>) ostream)
  "Serializes a message object of type '<recon_req-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'path) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <recon_req-response>) istream)
  "Deserializes a message object of type '<recon_req-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'path) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<recon_req-response>)))
  "Returns string type for a service object of type '<recon_req-response>"
  "modules/recon_reqResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'recon_req-response)))
  "Returns string type for a service object of type 'recon_req-response"
  "modules/recon_reqResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<recon_req-response>)))
  "Returns md5sum for a message object of type '<recon_req-response>"
  "504293a32ca80b6b20fe52b4cc8a6439")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'recon_req-response)))
  "Returns md5sum for a message object of type 'recon_req-response"
  "504293a32ca80b6b20fe52b4cc8a6439")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<recon_req-response>)))
  "Returns full string definition for message of type '<recon_req-response>"
  (cl:format cl:nil "nav_msgs/Path path~%~%~%================================================================================~%MSG: nav_msgs/Path~%#An array of poses that represents a Path for a robot to follow~%Header header~%geometry_msgs/PoseStamped[] poses~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'recon_req-response)))
  "Returns full string definition for message of type 'recon_req-response"
  (cl:format cl:nil "nav_msgs/Path path~%~%~%================================================================================~%MSG: nav_msgs/Path~%#An array of poses that represents a Path for a robot to follow~%Header header~%geometry_msgs/PoseStamped[] poses~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <recon_req-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'path))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <recon_req-response>))
  "Converts a ROS message object to a list"
  (cl:list 'recon_req-response
    (cl:cons ':path (path msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'recon_req)))
  'recon_req-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'recon_req)))
  'recon_req-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'recon_req)))
  "Returns string type for a service object of type '<recon_req>"
  "modules/recon_req")