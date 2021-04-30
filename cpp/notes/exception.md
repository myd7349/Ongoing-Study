1. std::throw_with_nested

   > ```cpp
   > // https://github.com/ess-dmsc/h5cpp/blob/f080aa729df63193c8bf95c461edb3a1d2c7cbcd/src/h5cpp/attribute/attribute.cpp#L43-L50
   >   try
   >   {
   >     handle = ObjectHandle(H5Aget_type(static_cast<hid_t>(handle_)));
   >   }
   >   catch(const std::runtime_error &)
   >   {
   >     std::throw_with_nested(std::runtime_error("Failure to obtain the datatype of an attribute!"));
   >   }
   > ```

