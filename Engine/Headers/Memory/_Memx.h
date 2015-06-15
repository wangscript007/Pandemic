/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
struct _Memx // Block Based Extended Container Base - Do not use this class, use 'Memx' instead
{
   void del  ();
   void clear();

    Int   absElms ()C {return               _abs.elms();}
    Int validElms ()C {return             _valid.elms();}
    Int      elms ()C {return             _valid.elms();}
   UInt   elmSize ()C {return _abs.elmSize()-SIZE(UInt);}
   UInt   memUsage()C;

   Ptr   absElm  (Int i)C {return (Byte*)_abs  [i]+SIZE(UInt);}
   Ptr validElm  (Int i)C {return absElm(_valid[i]);}
   Ptr addr      (Int i)C {return InRange(i, T) ? T[i] : NULL;}
   Ptr operator[](Int i)C {return validElm(i);}
   Ptr first     (     )C {return validElm(0);}
   Ptr last      (     )C {return validElm(validElms()-1);}
   Ptr New       (     );
   Ptr NewAt     (Int i);

   Int  validToAbsIndex(Int  valid)C;
   Int  absToValidIndex(Int  abs  )C;
   Int  validIndex     (CPtr elm  )C;
   Int    absIndex     (CPtr elm  )C;
   Bool   contains     (CPtr elm  )C {return validIndex(elm)!=-1;}

   void removeAbs  (Int  i  , Bool keep_order=false);
   void removeValid(Int  i  , Bool keep_order=false);
   void removeData (CPtr elm, Bool keep_order=false);
   void removeLast ();

   void setNum(Int num);
   Int  addNum(Int num);

   void reverseOrder();
   void    swapOrder(Int i, Int j);
   void moveElm     (Int elm, Int new_index);
   void moveToStart (Int elm);
   void moveToEnd   (Int elm);

   void saveRaw(File &f)C;
   Bool loadRaw(File &f) ;

 ~_Memx() {del();}

private:
  _Memb       _abs;
   Memc<UInt> _valid, _invalid;
   void     (*_new)(Ptr elm),
            (*_del)(Ptr elm);

         _Memx(Int elm_size, Int block_elms, void (*_new)(Ptr elm), void (*_del)(Ptr elm));
   void _reset(Int elm_size, Int block_elms, void (*_new)(Ptr elm), void (*_del)(Ptr elm));
   struct Abstract{};
   NO_COPY_CONSTRUCTOR(_Memx);
   T1(TYPE) friend struct Memx;
   T1(TYPE) friend struct MemxAbstract;
};
/******************************************************************************/
