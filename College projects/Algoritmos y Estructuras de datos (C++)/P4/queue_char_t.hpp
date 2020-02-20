
 namespace AED {

    class queue_char_t {
    private:
	dll_t list_;

    public:
	queue_char_t(void);
	virtual ~queue_char_t(void);

	    void put(char c);
	    char get(void);

	    bol empty(void);

      ostream& write(ostream& os);
    };
 }