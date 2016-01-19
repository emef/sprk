################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################

module Sprk
  module FFI

    # TODO
    # @note This class is 100% generated using zproject.
    class Blockdata
      # Raised when one tries to use an instance of {Blockdata} after
      # the internal pointer to the native object has been nullified.
      class DestroyedError < RuntimeError; end

      # Boilerplate for self pointer, initializer, and finalizer
      class << self
        alias :__new :new
      end
      # Attaches the pointer _ptr_ to this instance and defines a finalizer for
      # it if necessary.
      # @param ptr [::FFI::Pointer]
      # @param finalize [Boolean]
      def initialize(ptr, finalize = true)
        @ptr = ptr
        if @ptr.null?
          @ptr = nil # Remove null pointers so we don't have to test for them.
        elsif finalize
          @finalizer = self.class.create_finalizer_for @ptr
          ObjectSpace.define_finalizer self, @finalizer
        end
      end
      # @param ptr [::FFI::Pointer]
      # @return [Proc]
      def self.create_finalizer_for(ptr)
        Proc.new do
          ptr_ptr = ::FFI::MemoryPointer.new :pointer
          ptr_ptr.write_pointer ptr
          ::Sprk::FFI.sprk_blockdata_destroy ptr_ptr
        end
      end
      # @return [Boolean]
      def null?
        !@ptr or @ptr.null?
      end
      # Return internal pointer
      # @return [::FFI::Pointer]
      def __ptr
        raise DestroyedError unless @ptr
        @ptr
      end
      # So external Libraries can just pass the Object to a FFI function which expects a :pointer
      alias_method :to_ptr, :__ptr
      # Nullify internal pointer and return pointer pointer.
      # @note This detaches the current instance from the native object
      #   and thus makes it unusable.
      # @return [::FFI::MemoryPointer] the pointer pointing to a pointer
      #   pointing to the native object
      def __ptr_give_ref
        raise DestroyedError unless @ptr
        ptr_ptr = ::FFI::MemoryPointer.new :pointer
        ptr_ptr.write_pointer @ptr
        __undef_finalizer if @finalizer
        @ptr = nil
        ptr_ptr
      end
      # Undefines the finalizer for this object.
      # @note Only use this if you need to and can guarantee that the native
      #   object will be freed by other means.
      # @return [void]
      def __undef_finalizer
        ObjectSpace.undefine_finalizer self
        @finalizer = nil
      end

      # Create a new sprk_blockdata.
      # @param block [Block, #__ptr]
      # @param data [::FFI::Pointer, #to_ptr]
      # @param length [Integer, #to_int, #to_i]
      # @return [Sprk::Blockdata]
      def self.new(block, data, length)
        block = block.__ptr if block
        length = Integer(length)
        ptr = ::Sprk::FFI.sprk_blockdata_new(block, data, length)
        __new ptr
      end

      # Destroy the sprk_blockdata.
      #
      # @return [void]
      def destroy()
        return unless @ptr
        self_p = __ptr_give_ref
        result = ::Sprk::FFI.sprk_blockdata_destroy(self_p)
        result
      end

      # Queue a transformation to be applied to this block.
      #
      # @param transform [Transform, #__ptr]
      # @return [void]
      def queue_transform(transform)
        raise DestroyedError unless @ptr
        self_p = @ptr
        transform = transform.__ptr if transform
        result = ::Sprk::FFI.sprk_blockdata_queue_transform(self_p, transform)
        result
      end

      # 
      #
      # @return [Descriptor]
      def descriptor()
        raise DestroyedError unless @ptr
        self_p = @ptr
        result = ::Sprk::FFI.sprk_blockdata_descriptor(self_p)
        result = Descriptor.__new result, false
        result
      end

      # Self test of this class.
      #
      # @param verbose [Boolean]
      # @return [void]
      def self.test(verbose)
        verbose = !(0==verbose||!verbose) # boolean
        result = ::Sprk::FFI.sprk_blockdata_test(verbose)
        result
      end
    end
  end
end

################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
