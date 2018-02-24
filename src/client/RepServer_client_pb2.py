# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: RepServer_client.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='RepServer_client.proto',
  package='',
  syntax='proto2',
  serialized_pb=_b('\n\x16RepServer_client.proto\"\xe3\x02\n\x07Request\x12\"\n\x04type\x18\x01 \x02(\x0e\x32\x14.Request.RequestType\x12$\n\x05redis\x18\x02 \x01(\x0b\x32\x15.Request.RedisRequest\x12&\n\x06master\x18\x03 \x01(\x0b\x32\x16.Request.MasterRequest\x1a%\n\x07\x41\x64\x64ress\x12\x0c\n\x04host\x18\x01 \x02(\t\x12\x0c\n\x04port\x18\x02 \x02(\x05\x1a\\\n\x0cRedisRequest\x12%\n\x0b\x63lient_addr\x18\x01 \x02(\x0b\x32\x10.Request.Address\x12\x0b\n\x03\x63md\x18\x02 \x02(\t\x12\x0b\n\x03key\x18\x03 \x02(\t\x12\x0b\n\x03val\x18\x04 \x01(\t\x1a;\n\rMasterRequest\x12*\n\x10next_server_addr\x18\x01 \x01(\x0b\x32\x10.Request.Address\"$\n\x0bRequestType\x12\t\n\x05REDIS\x10\x00\x12\n\n\x06MASTER\x10\x01\"&\n\x05Reply\x12\x0b\n\x03key\x18\x01 \x02(\t\x12\x10\n\x08response\x18\x02 \x02(\t')
)



_REQUEST_REQUESTTYPE = _descriptor.EnumDescriptor(
  name='RequestType',
  full_name='Request.RequestType',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='REDIS', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MASTER', index=1, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=346,
  serialized_end=382,
)
_sym_db.RegisterEnumDescriptor(_REQUEST_REQUESTTYPE)


_REQUEST_ADDRESS = _descriptor.Descriptor(
  name='Address',
  full_name='Request.Address',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='host', full_name='Request.Address.host', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='port', full_name='Request.Address.port', index=1,
      number=2, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=152,
  serialized_end=189,
)

_REQUEST_REDISREQUEST = _descriptor.Descriptor(
  name='RedisRequest',
  full_name='Request.RedisRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='client_addr', full_name='Request.RedisRequest.client_addr', index=0,
      number=1, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='cmd', full_name='Request.RedisRequest.cmd', index=1,
      number=2, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='key', full_name='Request.RedisRequest.key', index=2,
      number=3, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='val', full_name='Request.RedisRequest.val', index=3,
      number=4, type=9, cpp_type=9, label=1,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=191,
  serialized_end=283,
)

_REQUEST_MASTERREQUEST = _descriptor.Descriptor(
  name='MasterRequest',
  full_name='Request.MasterRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='next_server_addr', full_name='Request.MasterRequest.next_server_addr', index=0,
      number=1, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=285,
  serialized_end=344,
)

_REQUEST = _descriptor.Descriptor(
  name='Request',
  full_name='Request',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='type', full_name='Request.type', index=0,
      number=1, type=14, cpp_type=8, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='redis', full_name='Request.redis', index=1,
      number=2, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='master', full_name='Request.master', index=2,
      number=3, type=11, cpp_type=10, label=1,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[_REQUEST_ADDRESS, _REQUEST_REDISREQUEST, _REQUEST_MASTERREQUEST, ],
  enum_types=[
    _REQUEST_REQUESTTYPE,
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=27,
  serialized_end=382,
)


_REPLY = _descriptor.Descriptor(
  name='Reply',
  full_name='Reply',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='key', full_name='Reply.key', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
    _descriptor.FieldDescriptor(
      name='response', full_name='Reply.response', index=1,
      number=2, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None, file=DESCRIPTOR),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=384,
  serialized_end=422,
)

_REQUEST_ADDRESS.containing_type = _REQUEST
_REQUEST_REDISREQUEST.fields_by_name['client_addr'].message_type = _REQUEST_ADDRESS
_REQUEST_REDISREQUEST.containing_type = _REQUEST
_REQUEST_MASTERREQUEST.fields_by_name['next_server_addr'].message_type = _REQUEST_ADDRESS
_REQUEST_MASTERREQUEST.containing_type = _REQUEST
_REQUEST.fields_by_name['type'].enum_type = _REQUEST_REQUESTTYPE
_REQUEST.fields_by_name['redis'].message_type = _REQUEST_REDISREQUEST
_REQUEST.fields_by_name['master'].message_type = _REQUEST_MASTERREQUEST
_REQUEST_REQUESTTYPE.containing_type = _REQUEST
DESCRIPTOR.message_types_by_name['Request'] = _REQUEST
DESCRIPTOR.message_types_by_name['Reply'] = _REPLY
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

Request = _reflection.GeneratedProtocolMessageType('Request', (_message.Message,), dict(

  Address = _reflection.GeneratedProtocolMessageType('Address', (_message.Message,), dict(
    DESCRIPTOR = _REQUEST_ADDRESS,
    __module__ = 'RepServer_client_pb2'
    # @@protoc_insertion_point(class_scope:Request.Address)
    ))
  ,

  RedisRequest = _reflection.GeneratedProtocolMessageType('RedisRequest', (_message.Message,), dict(
    DESCRIPTOR = _REQUEST_REDISREQUEST,
    __module__ = 'RepServer_client_pb2'
    # @@protoc_insertion_point(class_scope:Request.RedisRequest)
    ))
  ,

  MasterRequest = _reflection.GeneratedProtocolMessageType('MasterRequest', (_message.Message,), dict(
    DESCRIPTOR = _REQUEST_MASTERREQUEST,
    __module__ = 'RepServer_client_pb2'
    # @@protoc_insertion_point(class_scope:Request.MasterRequest)
    ))
  ,
  DESCRIPTOR = _REQUEST,
  __module__ = 'RepServer_client_pb2'
  # @@protoc_insertion_point(class_scope:Request)
  ))
_sym_db.RegisterMessage(Request)
_sym_db.RegisterMessage(Request.Address)
_sym_db.RegisterMessage(Request.RedisRequest)
_sym_db.RegisterMessage(Request.MasterRequest)

Reply = _reflection.GeneratedProtocolMessageType('Reply', (_message.Message,), dict(
  DESCRIPTOR = _REPLY,
  __module__ = 'RepServer_client_pb2'
  # @@protoc_insertion_point(class_scope:Reply)
  ))
_sym_db.RegisterMessage(Reply)


# @@protoc_insertion_point(module_scope)
