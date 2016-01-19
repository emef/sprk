/*  =========================================================================
    sprk_msg - sprk msg protocol

    Codec header for sprk_msg.

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

#ifndef SPRK_MSG_H_INCLUDED
#define SPRK_MSG_H_INCLUDED

/*  These are the sprk_msg messages:

    ASSIGN_BLOCK - 
        block_id            string      
        descriptor_uri      string      
        descriptor_offset   number 8    
        descriptor_length   number 8    
        descriptor_row_size  number 4   
*/


#define SPRK_MSG_ASSIGN_BLOCK               1

#include <czmq.h>

#ifdef __cplusplus
extern "C" {
#endif

//  Opaque class structure
#ifndef SPRK_MSG_T_DEFINED
typedef struct _sprk_msg_t sprk_msg_t;
#define SPRK_MSG_T_DEFINED
#endif

//  @interface
//  Create a new empty sprk_msg
sprk_msg_t *
    sprk_msg_new (void);

//  Destroy a sprk_msg instance
void
    sprk_msg_destroy (sprk_msg_t **self_p);

//  Receive a sprk_msg from the socket. Returns 0 if OK, -1 if
//  there was an error. Blocks if there is no message waiting.
int
    sprk_msg_recv (sprk_msg_t *self, zsock_t *input);

//  Send the sprk_msg to the output socket, does not destroy it
int
    sprk_msg_send (sprk_msg_t *self, zsock_t *output);


//  Print contents of message to stdout
void
    sprk_msg_print (sprk_msg_t *self);

//  Get/set the message routing id
zframe_t *
    sprk_msg_routing_id (sprk_msg_t *self);
void
    sprk_msg_set_routing_id (sprk_msg_t *self, zframe_t *routing_id);

//  Get the sprk_msg id and printable command
int
    sprk_msg_id (sprk_msg_t *self);
void
    sprk_msg_set_id (sprk_msg_t *self, int id);
const char *
    sprk_msg_command (sprk_msg_t *self);

//  Get/set the block_id field
const char *
    sprk_msg_block_id (sprk_msg_t *self);
void
    sprk_msg_set_block_id (sprk_msg_t *self, const char *value);

//  Get/set the descriptor_uri field
const char *
    sprk_msg_descriptor_uri (sprk_msg_t *self);
void
    sprk_msg_set_descriptor_uri (sprk_msg_t *self, const char *value);

//  Get/set the descriptor_offset field
uint64_t
    sprk_msg_descriptor_offset (sprk_msg_t *self);
void
    sprk_msg_set_descriptor_offset (sprk_msg_t *self, uint64_t descriptor_offset);

//  Get/set the descriptor_length field
uint64_t
    sprk_msg_descriptor_length (sprk_msg_t *self);
void
    sprk_msg_set_descriptor_length (sprk_msg_t *self, uint64_t descriptor_length);

//  Get/set the descriptor_row_size field
uint32_t
    sprk_msg_descriptor_row_size (sprk_msg_t *self);
void
    sprk_msg_set_descriptor_row_size (sprk_msg_t *self, uint32_t descriptor_row_size);

//  Self test of this class
void
    sprk_msg_test (bool verbose);
//  @end

//  For backwards compatibility with old codecs
#define sprk_msg_dump       sprk_msg_print

#ifdef __cplusplus
}
#endif

#endif
