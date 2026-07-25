# How Utility Works

Utility is not an application framework. It is a shared library of helpers that
the other libraries build on.

## Usage Pattern

1. Include the header that matches the data or helper you need.
2. Use the math, graphics, event, or logging type directly.
3. Keep platform-specific behavior in the upper layers.

## Typical Consumers

- Evan uses utility math, graphics, and asset types.
- Guillaume uses utility events, graphics, and data helpers.
- XIDER uses the shared types through Evan and Guillaume.

## Practical Rule

Utility should stay generic. If a type starts depending on application logic,
it belongs in a higher-level library instead.
