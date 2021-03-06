#ifndef dplyr_Result_CallbackProcessor_H
#define dplyr_Result_CallbackProcessor_H

namespace dplyr{
     
    // classes inherit from this template when they have a method with this signature
    // SEXP process_chunk( const SlicingIndex& indices)
    // 
    // the first time process_chunk is called, CallbackProcessor finds the right type
    // for storing the results, and it creates a suitable DelayedProcessor
    // object which is then used to fill the vector
    //
    // DelayedReducer is an example on how CallbackReducer is used
    //
    // it is assumed that the SEXP comes from evaluating some R expression, so
    // it should be one of a integer vector of length one, a numeric vector of 
    // length one or a character vector of length one
    template <typename CLASS>
    class CallbackProcessor : public Result {
    public:
        CallbackProcessor(){}
        
        virtual SEXP process( const GroupedDataFrame& gdf){
            Shelter<SEXP> __ ;
            CLASS* obj = static_cast<CLASS*>( this ) ;
            GroupedDataFrame::group_iterator git = gdf.group_begin() ;
            
            // first call, we don't know yet the type
            SEXP first_result = __( obj->process_chunk(*git) );
            
            // get the appropriate Delayed Processor to handle it
            DelayedProcessor_Base<CLASS>* processor = get_delayed_processor<CLASS>(first_result) ;
            if(!processor)
                stop( "expecting a single value" );
            SEXP res = __( processor->delayed_process( gdf, first_result, obj ) ) ;
            
            delete processor ;
            
            return res ;        
        }
        
        virtual SEXP process( const Rcpp::FullDataFrame& df){
            CLASS* obj = static_cast<CLASS*>(this) ;
            return obj->process_chunk(df.get_index()) ;    
        }
        
    } ;
    
}
#endif
