#swish internal serialization

Internally - swish makes use of protobuf for de/serialization. All control messages are essentially protobuf messages. All flavors of swish will use these messages to coordinate amongst each other. The actual messages sent by applications will be an opaque blob as far as swish is concerned.
