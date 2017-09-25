template<uint8_t... ArgSizes>
Instruction<ArgSizes...>::Instruction()
{
    static_assert(sizeof...(ArgSizes) == 0, "Not Default Constructible");
}

template<uint8_t... ArgSizes>
Instruction<ArgSizes...>::Instruction(uint8_t args_raw)
{
    assert((ArgSizes+...) <= 8);

    set_arg(args_raw);
}

template<uint8_t... ArgSizes>
uint8_t Instruction<ArgSizes...>::get_argument(uint8_t arg_index) const
{
    return args.at(arg_index);
}

template<uint8_t... ArgSizes>
void Instruction<ArgSizes...>::sync(Registers& registers)
{

}

template<uint8_t... ArgSizes>
template<uint8_t... OtherArgSizes, uint8_t LastArgSize>
void Instruction<ArgSizes...>::set_arg(uint8_t args_raw, uint8_t i)
{
    assert(LastArgSize > 0);

    args.at(i) = args_raw & (1 << (LastArgSize - 1));

    set_arg<OtherArgSizes...>(args_raw >> LastArgSize, static_cast<uint8_t>(i - 1));

}

template<uint8_t... ArgSizes>
void Instruction<ArgSizes...>::set_arg(uint8_t args_raw)
{
    set_arg<ArgSizes...>(args_raw, args.size());
}

template<uint8_t... ArgSizes>
template<uint8_t LastArgSize>
void Instruction<ArgSizes...>::set_arg(uint8_t args_raw, uint8_t i)
{
    assert(LastArgSize > 0);
    assert(i == 0);

    args.at(i) = args_raw & (1 << (LastArgSize - 1));

}
