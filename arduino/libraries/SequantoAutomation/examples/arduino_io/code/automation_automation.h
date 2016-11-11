#ifdef __cplusplus
extern "C" {
#endif
#ifdef SQ_DISABLE_AUTOMATION_INTERFACE
#define sq_sequanto_automation_version_updated(...) { do {} while(0); }
#define sq_digital_direction_updated(...) { do {} while(0); }
#define sq_digital_pin_updated(...) { do {} while(0); }
#define sq_digital_counter_updated(...) { do {} while(0); }
#define sq_digital_counter_enabled_updated(...) { do {} while(0); }
#define sq_digital_count_on_high2low_updated(...) { do {} while(0); }
#define sq_digital_count_on_low2high_updated(...) { do {} while(0); }
#define sq_analog_raw_updated(...) { do {} while(0); }
#define sq_analog_value_updated(...) { do {} while(0); }
#else /* SQ_DISABLE_AUTOMATION_INTERFACE */
void sq_sequanto_automation_version_updated ( const char * _value );
void sq_digital_direction_updated ( int _pin, const char * _value );
void sq_digital_pin_updated ( int _pin, SQBool _value );
void sq_digital_counter_updated ( int _pin, int _value );
void sq_digital_counter_enabled_updated ( int _pin, SQBool _value );
void sq_digital_count_on_high2low_updated ( int _pin, SQBool _value );
void sq_digital_count_on_low2high_updated ( int _pin, SQBool _value );
void sq_analog_raw_updated ( int _pin, int _value );
void sq_analog_value_updated ( int _pin, int _value );
#endif /* SQ_DISABLE_AUTOMATION_INTERFACE */
#ifdef __cplusplus
}
#endif
