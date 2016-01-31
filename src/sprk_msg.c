/*  =========================================================================
    sprk_msg - sprk msg protocol

    Codec class for sprk_msg.

    ** WARNING *************************************************************
    THIS SOURCE FILE IS 100% GENERATED. If you edit this file, you will lose
    your changes at the next build cycle. This is great for temporary printf
    statements. DO NOT MAKE ANY CHANGES YOU WISH TO KEEP. The correct places
    for commits are:

     * The XML model used for this code generation: sprk_msg.xml, or
     * The code generation script that built this file: zproto_codec_c
    ************************************************************************
    =========================================================================
*/

/*
@header
    sprk_msg - sprk msg protocol
@discuss
@end
*/

#include "../include/sprk_msg.h"

//  Structure of our class

struct _sprk_msg_t {
    zframe_t *routing_id;               //  Routing_id from ROUTER, if any
    int id;                             //  sprk_msg message ID
    byte *needle;                       //  Read/write pointer for serialization
    byte *ceiling;                      //  Valid upper limit for read pointer
    char block_id [256];                //  block_id
    char descriptor_uri [256];          //  descriptor_uri
    uint64_t descriptor_offset;         //  descriptor_offset
    uint64_t descriptor_length;         //  descriptor_length
    uint32_t descriptor_row_size;       //  descriptor_row_size
};

//  --------------------------------------------------------------------------
//  Network data encoding macros

//  Put a block of octets to the frame
#define PUT_OCTETS(host,size) { \
    memcpy (self->needle, (host), size); \
    self->needle += size; \
}

//  Get a block of octets from the frame
#define GET_OCTETS(host,size) { \
    if (self->needle + size > self->ceiling) { \
        zsys_warning ("sprk_msg: GET_OCTETS failed"); \
        goto malformed; \
    } \
    memcpy ((host), self->needle, size); \
    self->needle += size; \
}

//  Put a 1-byte number to the frame
#define PUT_NUMBER1(host) { \
    *(byte *) self->needle = (host); \
    self->needle++; \
}

//  Put a 2-byte number to the frame
#define PUT_NUMBER2(host) { \
    self->needle [0] = (byte) (((host) >> 8)  & 255); \
    self->needle [1] = (byte) (((host))       & 255); \
    self->needle += 2; \
}

//  Put a 4-byte number to the frame
#define PUT_NUMBER4(host) { \
    self->needle [0] = (byte) (((host) >> 24) & 255); \
    self->needle [1] = (byte) (((host) >> 16) & 255); \
    self->needle [2] = (byte) (((host) >> 8)  & 255); \
    self->needle [3] = (byte) (((host))       & 255); \
    self->needle += 4; \
}

//  Put a 8-byte number to the frame
#define PUT_NUMBER8(host) { \
    self->needle [0] = (byte) (((host) >> 56) & 255); \
    self->needle [1] = (byte) (((host) >> 48) & 255); \
    self->needle [2] = (byte) (((host) >> 40) & 255); \
    self->needle [3] = (byte) (((host) >> 32) & 255); \
    self->needle [4] = (byte) (((host) >> 24) & 255); \
    self->needle [5] = (byte) (((host) >> 16) & 255); \
    self->needle [6] = (byte) (((host) >> 8)  & 255); \
    self->needle [7] = (byte) (((host))       & 255); \
    self->needle += 8; \
}

//  Get a 1-byte number from the frame
#define GET_NUMBER1(host) { \
    if (self->needle + 1 > self->ceiling) { \
        zsys_warning ("sprk_msg: GET_NUMBER1 failed"); \
        goto malformed; \
    } \
    (host) = *(byte *) self->needle; \
    self->needle++; \
}

//  Get a 2-byte number from the frame
#define GET_NUMBER2(host) { \
    if (self->needle + 2 > self->ceiling) { \
        zsys_warning ("sprk_msg: GET_NUMBER2 failed"); \
        goto malformed; \
    } \
    (host) = ((uint16_t) (self->needle [0]) << 8) \
           +  (uint16_t) (self->needle [1]); \
    self->needle += 2; \
}

//  Get a 4-byte number from the frame
#define GET_NUMBER4(host) { \
    if (self->needle + 4 > self->ceiling) { \
        zsys_warning ("sprk_msg: GET_NUMBER4 failed"); \
        goto malformed; \
    } \
    (host) = ((uint32_t) (self->needle [0]) << 24) \
           + ((uint32_t) (self->needle [1]) << 16) \
           + ((uint32_t) (self->needle [2]) << 8) \
           +  (uint32_t) (self->needle [3]); \
    self->needle += 4; \
}

//  Get a 8-byte number from the frame
#define GET_NUMBER8(host) { \
    if (self->needle + 8 > self->ceiling) { \
        zsys_warning ("sprk_msg: GET_NUMBER8 failed"); \
        goto malformed; \
    } \
    (host) = ((uint64_t) (self->needle [0]) << 56) \
           + ((uint64_t) (self->needle [1]) << 48) \
           + ((uint64_t) (self->needle [2]) << 40) \
           + ((uint64_t) (self->needle [3]) << 32) \
           + ((uint64_t) (self->needle [4]) << 24) \
           + ((uint64_t) (self->needle [5]) << 16) \
           + ((uint64_t) (self->needle [6]) << 8) \
           +  (uint64_t) (self->needle [7]); \
    self->needle += 8; \
}

//  Put a string to the frame
#define PUT_STRING(host) { \
    size_t string_size = strlen (host); \
    PUT_NUMBER1 (string_size); \
    memcpy (self->needle, (host), string_size); \
    self->needle += string_size; \
}

//  Get a string from the frame
#define GET_STRING(host) { \
    size_t string_size; \
    GET_NUMBER1 (string_size); \
    if (self->needle + string_size > (self->ceiling)) { \
        zsys_warning ("sprk_msg: GET_STRING failed"); \
        goto malformed; \
    } \
    memcpy ((host), self->needle, string_size); \
    (host) [string_size] = 0; \
    self->needle += string_size; \
}

//  Put a long string to the frame
#define PUT_LONGSTR(host) { \
    size_t string_size = strlen (host); \
    PUT_NUMBER4 (string_size); \
    memcpy (self->needle, (host), string_size); \
    self->needle += string_size; \
}

//  Get a long string from the frame
#define GET_LONGSTR(host) { \
    size_t string_size; \
    GET_NUMBER4 (string_size); \
    if (self->needle + string_size > (self->ceiling)) { \
        zsys_warning ("sprk_msg: GET_LONGSTR failed"); \
        goto malformed; \
    } \
    free ((host)); \
    (host) = (char *) malloc (string_size + 1); \
    memcpy ((host), self->needle, string_size); \
    (host) [string_size] = 0; \
    self->needle += string_size; \
}


//  --------------------------------------------------------------------------
//  Create a new sprk_msg

sprk_msg_t *
sprk_msg_new (void)
{
    sprk_msg_t *self = (sprk_msg_t *) zmalloc (sizeof (sprk_msg_t));
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the sprk_msg

void
sprk_msg_destroy (sprk_msg_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        sprk_msg_t *self = *self_p;

        //  Free class properties
        zframe_destroy (&self->routing_id);

        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}


//  --------------------------------------------------------------------------
//  Receive a sprk_msg from the socket. Returns 0 if OK, -1 if
//  there was an error. Blocks if there is no message waiting.

int
sprk_msg_recv (sprk_msg_t *self, zsock_t *input)
{
    assert (input);

    if (zsock_type (input) == ZMQ_ROUTER) {
        zframe_destroy (&self->routing_id);
        self->routing_id = zframe_recv (input);
        if (!self->routing_id || !zsock_rcvmore (input)) {
            zsys_warning ("sprk_msg: no routing ID");
            return -1;          //  Interrupted or malformed
        }
    }
    zmq_msg_t frame;
    zmq_msg_init (&frame);
    int size = zmq_msg_recv (&frame, zsock_resolve (input), 0);
    if (size == -1) {
        zsys_warning ("sprk_msg: interrupted");
        goto malformed;         //  Interrupted
    }
    //  Get and check protocol signature
    self->needle = (byte *) zmq_msg_data (&frame);
    self->ceiling = self->needle + zmq_msg_size (&frame);

    uint16_t signature;
    GET_NUMBER2 (signature);
    if (signature != (0xAAA0 | 0)) {
        zsys_warning ("sprk_msg: invalid signature");
        //  TODO: discard invalid messages and loop, and return
        //  -1 only on interrupt
        goto malformed;         //  Interrupted
    }
    //  Get message id and parse per message type
    GET_NUMBER1 (self->id);

    switch (self->id) {
        case SPRK_MSG_ASSIGN_BLOCK:
            GET_STRING (self->block_id);
            GET_STRING (self->descriptor_uri);
            GET_NUMBER8 (self->descriptor_offset);
            GET_NUMBER8 (self->descriptor_length);
            GET_NUMBER4 (self->descriptor_row_size);
            break;

        case SPRK_MSG_BLOCK_ASSIGNED:
            GET_STRING (self->block_id);
            break;

        default:
            zsys_warning ("sprk_msg: bad message ID");
            goto malformed;
    }
    //  Successful return
    zmq_msg_close (&frame);
    return 0;

    //  Error returns
    malformed:
        zsys_warning ("sprk_msg: sprk_msg malformed message, fail");
        zmq_msg_close (&frame);
        return -1;              //  Invalid message
}


//  --------------------------------------------------------------------------
//  Send the sprk_msg to the socket. Does not destroy it. Returns 0 if
//  OK, else -1.

int
sprk_msg_send (sprk_msg_t *self, zsock_t *output)
{
    assert (self);
    assert (output);

    if (zsock_type (output) == ZMQ_ROUTER)
        zframe_send (&self->routing_id, output, ZFRAME_MORE + ZFRAME_REUSE);

    size_t frame_size = 2 + 1;          //  Signature and message ID
    switch (self->id) {
        case SPRK_MSG_ASSIGN_BLOCK:
            frame_size += 1 + strlen (self->block_id);
            frame_size += 1 + strlen (self->descriptor_uri);
            frame_size += 8;            //  descriptor_offset
            frame_size += 8;            //  descriptor_length
            frame_size += 4;            //  descriptor_row_size
            break;
        case SPRK_MSG_BLOCK_ASSIGNED:
            frame_size += 1 + strlen (self->block_id);
            break;
    }
    //  Now serialize message into the frame
    zmq_msg_t frame;
    zmq_msg_init_size (&frame, frame_size);
    self->needle = (byte *) zmq_msg_data (&frame);
    PUT_NUMBER2 (0xAAA0 | 0);
    PUT_NUMBER1 (self->id);
    size_t nbr_frames = 1;              //  Total number of frames to send

    switch (self->id) {
        case SPRK_MSG_ASSIGN_BLOCK:
            PUT_STRING (self->block_id);
            PUT_STRING (self->descriptor_uri);
            PUT_NUMBER8 (self->descriptor_offset);
            PUT_NUMBER8 (self->descriptor_length);
            PUT_NUMBER4 (self->descriptor_row_size);
            break;

        case SPRK_MSG_BLOCK_ASSIGNED:
            PUT_STRING (self->block_id);
            break;

    }
    //  Now send the data frame
    zmq_msg_send (&frame, zsock_resolve (output), --nbr_frames? ZMQ_SNDMORE: 0);

    return 0;
}


//  --------------------------------------------------------------------------
//  Print contents of message to stdout

void
sprk_msg_print (sprk_msg_t *self)
{
    assert (self);
    switch (self->id) {
        case SPRK_MSG_ASSIGN_BLOCK:
            zsys_debug ("SPRK_MSG_ASSIGN_BLOCK:");
            zsys_debug ("    block_id='%s'", self->block_id);
            zsys_debug ("    descriptor_uri='%s'", self->descriptor_uri);
            zsys_debug ("    descriptor_offset=%ld", (long) self->descriptor_offset);
            zsys_debug ("    descriptor_length=%ld", (long) self->descriptor_length);
            zsys_debug ("    descriptor_row_size=%ld", (long) self->descriptor_row_size);
            break;

        case SPRK_MSG_BLOCK_ASSIGNED:
            zsys_debug ("SPRK_MSG_BLOCK_ASSIGNED:");
            zsys_debug ("    block_id='%s'", self->block_id);
            break;

    }
}


//  --------------------------------------------------------------------------
//  Get/set the message routing_id

zframe_t *
sprk_msg_routing_id (sprk_msg_t *self)
{
    assert (self);
    return self->routing_id;
}

void
sprk_msg_set_routing_id (sprk_msg_t *self, zframe_t *routing_id)
{
    if (self->routing_id)
        zframe_destroy (&self->routing_id);
    self->routing_id = zframe_dup (routing_id);
}


//  --------------------------------------------------------------------------
//  Get/set the sprk_msg id

int
sprk_msg_id (sprk_msg_t *self)
{
    assert (self);
    return self->id;
}

void
sprk_msg_set_id (sprk_msg_t *self, int id)
{
    self->id = id;
}

//  --------------------------------------------------------------------------
//  Return a printable command string

const char *
sprk_msg_command (sprk_msg_t *self)
{
    assert (self);
    switch (self->id) {
        case SPRK_MSG_ASSIGN_BLOCK:
            return ("ASSIGN_BLOCK");
            break;
        case SPRK_MSG_BLOCK_ASSIGNED:
            return ("BLOCK_ASSIGNED");
            break;
    }
    return "?";
}

//  --------------------------------------------------------------------------
//  Get/set the block_id field

const char *
sprk_msg_block_id (sprk_msg_t *self)
{
    assert (self);
    return self->block_id;
}

void
sprk_msg_set_block_id (sprk_msg_t *self, const char *value)
{
    assert (self);
    assert (value);
    if (value == self->block_id)
        return;
    strncpy (self->block_id, value, 255);
    self->block_id [255] = 0;
}


//  --------------------------------------------------------------------------
//  Get/set the descriptor_uri field

const char *
sprk_msg_descriptor_uri (sprk_msg_t *self)
{
    assert (self);
    return self->descriptor_uri;
}

void
sprk_msg_set_descriptor_uri (sprk_msg_t *self, const char *value)
{
    assert (self);
    assert (value);
    if (value == self->descriptor_uri)
        return;
    strncpy (self->descriptor_uri, value, 255);
    self->descriptor_uri [255] = 0;
}


//  --------------------------------------------------------------------------
//  Get/set the descriptor_offset field

uint64_t
sprk_msg_descriptor_offset (sprk_msg_t *self)
{
    assert (self);
    return self->descriptor_offset;
}

void
sprk_msg_set_descriptor_offset (sprk_msg_t *self, uint64_t descriptor_offset)
{
    assert (self);
    self->descriptor_offset = descriptor_offset;
}


//  --------------------------------------------------------------------------
//  Get/set the descriptor_length field

uint64_t
sprk_msg_descriptor_length (sprk_msg_t *self)
{
    assert (self);
    return self->descriptor_length;
}

void
sprk_msg_set_descriptor_length (sprk_msg_t *self, uint64_t descriptor_length)
{
    assert (self);
    self->descriptor_length = descriptor_length;
}


//  --------------------------------------------------------------------------
//  Get/set the descriptor_row_size field

uint32_t
sprk_msg_descriptor_row_size (sprk_msg_t *self)
{
    assert (self);
    return self->descriptor_row_size;
}

void
sprk_msg_set_descriptor_row_size (sprk_msg_t *self, uint32_t descriptor_row_size)
{
    assert (self);
    self->descriptor_row_size = descriptor_row_size;
}



//  --------------------------------------------------------------------------
//  Selftest

void
sprk_msg_test (bool verbose)
{
    printf (" * sprk_msg:");

    if (verbose)
        printf ("\n");

    //  @selftest
    //  Simple create/destroy test
    sprk_msg_t *self = sprk_msg_new ();
    assert (self);
    sprk_msg_destroy (&self);
    //  Create pair of sockets we can send through
    //  We must bind before connect if we wish to remain compatible with ZeroMQ < v4
    zsock_t *output = zsock_new (ZMQ_DEALER);
    assert (output);
    int rc = zsock_bind (output, "inproc://selftest-sprk_msg");
    assert (rc == 0);

    zsock_t *input = zsock_new (ZMQ_ROUTER);
    assert (input);
    rc = zsock_connect (input, "inproc://selftest-sprk_msg");
    assert (rc == 0);


    //  Encode/send/decode and verify each message type
    int instance;
    self = sprk_msg_new ();
    sprk_msg_set_id (self, SPRK_MSG_ASSIGN_BLOCK);

    sprk_msg_set_block_id (self, "Life is short but Now lasts for ever");
    sprk_msg_set_descriptor_uri (self, "Life is short but Now lasts for ever");
    sprk_msg_set_descriptor_offset (self, 123);
    sprk_msg_set_descriptor_length (self, 123);
    sprk_msg_set_descriptor_row_size (self, 123);
    //  Send twice
    sprk_msg_send (self, output);
    sprk_msg_send (self, output);

    for (instance = 0; instance < 2; instance++) {
        sprk_msg_recv (self, input);
        assert (sprk_msg_routing_id (self));
        assert (streq (sprk_msg_block_id (self), "Life is short but Now lasts for ever"));
        assert (streq (sprk_msg_descriptor_uri (self), "Life is short but Now lasts for ever"));
        assert (sprk_msg_descriptor_offset (self) == 123);
        assert (sprk_msg_descriptor_length (self) == 123);
        assert (sprk_msg_descriptor_row_size (self) == 123);
    }
    sprk_msg_set_id (self, SPRK_MSG_BLOCK_ASSIGNED);

    sprk_msg_set_block_id (self, "Life is short but Now lasts for ever");
    //  Send twice
    sprk_msg_send (self, output);
    sprk_msg_send (self, output);

    for (instance = 0; instance < 2; instance++) {
        sprk_msg_recv (self, input);
        assert (sprk_msg_routing_id (self));
        assert (streq (sprk_msg_block_id (self), "Life is short but Now lasts for ever"));
    }

    sprk_msg_destroy (&self);
    zsock_destroy (&input);
    zsock_destroy (&output);
    //  @end

    printf ("OK\n");
}
