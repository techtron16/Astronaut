# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from modules/target_reqRequest.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import geometry_msgs.msg

class target_reqRequest(genpy.Message):
  _md5sum = "4fabcdf1d38a4bd4d2e9f5a8ffe3985b"
  _type = "modules/target_reqRequest"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """geometry_msgs/Pose request

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of postion and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w
"""
  __slots__ = ['request']
  _slot_types = ['geometry_msgs/Pose']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       request

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(target_reqRequest, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.request is None:
        self.request = geometry_msgs.msg.Pose()
    else:
      self.request = geometry_msgs.msg.Pose()

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_struct_7d.pack(_x.request.position.x, _x.request.position.y, _x.request.position.z, _x.request.orientation.x, _x.request.orientation.y, _x.request.orientation.z, _x.request.orientation.w))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.request is None:
        self.request = geometry_msgs.msg.Pose()
      end = 0
      _x = self
      start = end
      end += 56
      (_x.request.position.x, _x.request.position.y, _x.request.position.z, _x.request.orientation.x, _x.request.orientation.y, _x.request.orientation.z, _x.request.orientation.w,) = _struct_7d.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_struct_7d.pack(_x.request.position.x, _x.request.position.y, _x.request.position.z, _x.request.orientation.x, _x.request.orientation.y, _x.request.orientation.z, _x.request.orientation.w))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.request is None:
        self.request = geometry_msgs.msg.Pose()
      end = 0
      _x = self
      start = end
      end += 56
      (_x.request.position.x, _x.request.position.y, _x.request.position.z, _x.request.orientation.x, _x.request.orientation.y, _x.request.orientation.z, _x.request.orientation.w,) = _struct_7d.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_7d = struct.Struct("<7d")
# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from modules/target_reqResponse.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import geometry_msgs.msg

class target_reqResponse(genpy.Message):
  _md5sum = "9958aa1aaae7c968676532566b770ba6"
  _type = "modules/target_reqResponse"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """geometry_msgs/Pose nav_point
int64 recon_type


================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of postion and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w
"""
  __slots__ = ['nav_point','recon_type']
  _slot_types = ['geometry_msgs/Pose','int64']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       nav_point,recon_type

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(target_reqResponse, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.nav_point is None:
        self.nav_point = geometry_msgs.msg.Pose()
      if self.recon_type is None:
        self.recon_type = 0
    else:
      self.nav_point = geometry_msgs.msg.Pose()
      self.recon_type = 0

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_struct_7dq.pack(_x.nav_point.position.x, _x.nav_point.position.y, _x.nav_point.position.z, _x.nav_point.orientation.x, _x.nav_point.orientation.y, _x.nav_point.orientation.z, _x.nav_point.orientation.w, _x.recon_type))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.nav_point is None:
        self.nav_point = geometry_msgs.msg.Pose()
      end = 0
      _x = self
      start = end
      end += 64
      (_x.nav_point.position.x, _x.nav_point.position.y, _x.nav_point.position.z, _x.nav_point.orientation.x, _x.nav_point.orientation.y, _x.nav_point.orientation.z, _x.nav_point.orientation.w, _x.recon_type,) = _struct_7dq.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_struct_7dq.pack(_x.nav_point.position.x, _x.nav_point.position.y, _x.nav_point.position.z, _x.nav_point.orientation.x, _x.nav_point.orientation.y, _x.nav_point.orientation.z, _x.nav_point.orientation.w, _x.recon_type))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.nav_point is None:
        self.nav_point = geometry_msgs.msg.Pose()
      end = 0
      _x = self
      start = end
      end += 64
      (_x.nav_point.position.x, _x.nav_point.position.y, _x.nav_point.position.z, _x.nav_point.orientation.x, _x.nav_point.orientation.y, _x.nav_point.orientation.z, _x.nav_point.orientation.w, _x.recon_type,) = _struct_7dq.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_7dq = struct.Struct("<7dq")
class target_req(object):
  _type          = 'modules/target_req'
  _md5sum = 'ab16145b44c7b4e33fd358e08d9aef29'
  _request_class  = target_reqRequest
  _response_class = target_reqResponse
