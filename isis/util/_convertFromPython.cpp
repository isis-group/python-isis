#include "_convertFromPython.hpp"

namespace isis
{
namespace python
{
namespace util
{
namespace _internal
{


const std::list<std::string> ConvertFromPython::knownTypes = isis::util::stringToList<std::string>( "complex datetime.datetime datetime.date bool list str float double int ivector4 dvector4 fvector4 Selection" );

template<>
void getValueFromPyObject<boost::gregorian::date> ( isis::util::Value<boost::gregorian::date> &ref, api::object value )
{
	PyDateTime_IMPORT;
	boost::gregorian::greg_year year = PyDateTime_GET_YEAR( value.ptr() );
	boost::gregorian::greg_month month =  PyDateTime_GET_MONTH( value.ptr() );
	boost::gregorian::greg_day day = PyDateTime_GET_DAY( value.ptr() );
	ref = isis::util::Value<boost::gregorian::date> ( boost::gregorian::date( year, month, day ) );
}

template<>
void getValueFromPyObject< boost::posix_time::ptime >( isis::util::Value< boost::posix_time::ptime >& ref, api::object value )
{
	PyDateTime_IMPORT;
	boost::gregorian::greg_year year = PyDateTime_GET_YEAR( value.ptr() );
	boost::gregorian::greg_month month =  PyDateTime_GET_MONTH( value.ptr() );
	boost::gregorian::greg_day day = PyDateTime_GET_DAY( value.ptr() );
	boost::gregorian::date date( year, month, day );
	boost::posix_time::time_duration::hour_type hours = PyDateTime_DATE_GET_HOUR( value.ptr() );
	boost::posix_time::time_duration::min_type minutes = PyDateTime_DATE_GET_MINUTE( value.ptr() );
	boost::posix_time::time_duration::sec_type seconds = PyDateTime_DATE_GET_SECOND( value.ptr() );
	boost::posix_time::time_duration time_duration( hours, minutes, seconds );
	ref = isis::util::Value<boost::posix_time::ptime>( boost::posix_time::ptime( date, time_duration ) );
}




isis::util::PropertyValue ConvertFromPython::convert( api::object value )
{
	PyDateTime_IMPORT;
	std::string typeName = value.ptr()->ob_type->tp_name;

	// check if we know this type
	if( std::find( ConvertFromPython::knownTypes.begin(), ConvertFromPython::knownTypes.begin(), typeName ) == ConvertFromPython::knownTypes.end() ) {
		LOG( isis::util::Runtime, error ) << "No conversion from type " << typeName << " available.";
		return isis::util::PropertyValue();
	}

	//check for basic python types
	if( PyInt_Check( value.ptr() ) ) {
		isis::util::Value<int32_t> vRef;
		getValueFromPyObject<int32_t>( vRef, value );
		return vRef;
	} else if ( PyBool_Check( value.ptr() ) ) {
		isis::util::Value<bool> vRef;
		getValueFromPyObject<bool>( vRef, value );
		return vRef;
	} else if ( PyFloat_Check( value.ptr() ) ) {
		isis::util::Value<float> vRef;
		getValueFromPyObject<float>( vRef, value );
		return vRef;
	} else if ( PyString_Check( value.ptr() ) ) {
		isis::util::Value<std::string> vRef;
		getValueFromPyObject<std::string>( vRef, value );
		return vRef;
	} else if ( PyLong_Check( value.ptr() ) ) {
		isis::util::Value<int64_t> vRef;
		getValueFromPyObject<int64_t>( vRef, value );
		return vRef;
	}  else if ( typeName == std::string( "ivector4" ) ) {
		isis::util::Value<isis::util::ivector4> vRef;
		getValueFromPyObject<isis::util::ivector4>( vRef, value );
		return vRef;
	} else if ( typeName == std::string( "fvector4" ) ) {
		isis::util::Value<isis::util::fvector4> vRef;
		getValueFromPyObject<isis::util::fvector4>( vRef, value );
		return vRef;
	} else if ( typeName == std::string( "dvector4" ) ) {
		isis::util::Value<isis::util::dvector4> vRef;
		getValueFromPyObject<isis::util::dvector4>( vRef, value );
		return vRef;
	} else if ( typeName == std::string( "Selection" ) ) {
		isis::util::Value<isis::util::Selection> vRef;
		getValueFromPyObject<isis::util::Selection>( vRef, value );
		return vRef;
	} else if ( PyDate_CheckExact( value.ptr() ) ) {
		isis::util::Value<boost::gregorian::date> vRef;
		getValueFromPyObject<boost::gregorian::date>( vRef, value );
		return vRef;
	} else if ( PyDateTime_CheckExact( value.ptr() ) ) {
		isis::util::Value<boost::posix_time::ptime> vRef;
		getValueFromPyObject< boost::posix_time::ptime >( vRef, value );
		return vRef;
	} else if ( PyComplex_Check( value.ptr() ) )  {
		isis::util::Value<std::complex<double> > vRef;
		getValueFromPyObject<std::complex<double> >( vRef, value );
		return vRef;
		//we have a list....
	} else if ( PyList_Check( value.ptr() ) ) {
		return getList( value );

	} else {
		LOG( isis::util::Runtime, error ) << "Type " << typeName << " is not known.";
	}

	return isis::util::PropertyValue();
}


isis::util::PropertyValue ConvertFromPython::getList( api::object value )
{
	std::list<std::string> types;

	for( Py_ssize_t i = 0; i < PyList_Size( value.ptr() ); i++ ) {
		types.push_back( PyList_GetItem( value.ptr(), i )->ob_type->tp_name );
	}

	if( std::find( types.begin(), types.end(), std::string( "str" ) ) != types.end() ) {
		return isis::util::Value< isis::util::slist > ( extractFromList<std::string>( value ) );
	} else if( std::find( types.begin(), types.end(), std::string( "float" ) ) != types.end() ) {
		return isis::util::Value< isis::util::dlist > ( extractFromList<double>( value ) );
	} else if( std::find( types.begin(), types.end(), std::string( "int" ) ) != types.end() ) {
		return isis::util::Value< isis::util::ilist > ( extractFromList<int32_t>( value ) );
	} else {
		LOG( isis::util::Runtime, error ) << "The list contains elements of type that can not be converted!";
	}

	return isis::util::PropertyValue();
}

}
}
}
} // end namespace
